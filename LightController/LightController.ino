const int RED_LED = 30;
const int GREEN_LED = 31;
const int YELLOW_LED = 32;
const int BLUE_LED = 33;
const int BUTTON = 2;

const int standardDelay = 100;
const int longDelay = 200;

int lastBlinkTime = -1;

int sosIt = 0;

enum Color {
  RED, GREEN, YELLOW, BLUE
} lightColor = BLUE;

enum Mode {
  STATIC, BLINKING, SOS, DISCO1, DISCO2, OFF
} lightMode = OFF;

void setup() {
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  turnLightsOff();
}

void loop() {
  int b = readButton();
  if (b == 1) { // single click
    toggleLight();
  } else if (lightMode != OFF && b == 2) { // double click
    switchColor();
    turnLightsOff();
  } else if (lightMode != OFF && b == 3) { // click + hold
    switchLightMode();
    turnLightsOff();
  }
  updateLEDs();
}

void updateLEDs() {
  int ledPin = getLEDPin(lightColor);
  int currentTime = millis();
  if (lightMode == STATIC) {
    digitalWrite(ledPin, HIGH);
  } else if (lightMode == BLINKING) {
    if (currentTime - lastBlinkTime > standardDelay) {
      lastBlinkTime = currentTime;
      digitalWrite(ledPin, !digitalRead(ledPin));
    }
  } else if (lightMode == SOS) {
    int sosPart = sosIt / 3;
    if (sosIt == 9) {
      if (currentTime - lastBlinkTime > 3 * longDelay) {
        sosIt = 0;
      }
    } else if (sosPart % 2 == 0) {
      if (currentTime - lastBlinkTime > standardDelay) {
        lastBlinkTime = currentTime;
        digitalWrite(ledPin, !digitalRead(ledPin));
        if (digitalRead(ledPin) == LOW) {
          sosIt++;
        }
      }
    } else {
      if (currentTime - lastBlinkTime > longDelay) {
        lastBlinkTime = currentTime;
        digitalWrite(ledPin, !digitalRead(ledPin));
        if (digitalRead(ledPin) == LOW) {
          sosIt++;
        }
      }
    }
  } else if (lightMode == DISCO1) {
    if (currentTime - lastBlinkTime > standardDelay) {
      lastBlinkTime = currentTime;
      digitalWrite(ledPin, !digitalRead(ledPin));
      if (digitalRead(ledPin) == LOW) {
        switchColor();
      }
    }
  } else if (lightMode == DISCO2) {
    if (currentTime - lastBlinkTime > standardDelay) {
      lastBlinkTime = currentTime;
      digitalWrite(ledPin, !digitalRead(ledPin));
      switchColor();
    }
  } else {
    turnLightsOff();
    lightColor = BLUE;
  }
}

void turnLightsOff() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

void toggleLight() {
  if (lightMode == OFF) {
    lightMode = STATIC;
  } else {
    lightMode = OFF;
  }
}

void switchColor() {
  if (lightColor == RED) {
    lightColor = GREEN;
  } else if (lightColor == GREEN) {
    lightColor = YELLOW;
  } else if (lightColor == YELLOW) {
    lightColor = BLUE;
  } else {
    lightColor = RED;
  }
}

void switchLightMode() {
  if (lightMode == STATIC) {
    lightMode = BLINKING;
  } else if (lightMode == BLINKING) {
    lightMode = SOS;
  } else if (lightMode == SOS) {
    lightMode = DISCO1;
  } else if (lightMode == DISCO1) {
    lightMode = DISCO2;
  } else {
    lightMode = STATIC;
  }
}

int getLEDPin(Color color) {
  if (color == RED) {
    return RED_LED;
  } else if (color == GREEN) {
    return GREEN_LED;
  } else if (color == YELLOW) {
    return YELLOW_LED;
  } else {
    return BLUE_LED;
  }
}
