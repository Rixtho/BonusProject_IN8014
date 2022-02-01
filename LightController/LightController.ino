const int RED_LED = 40;
const int GREEN_LED = 22;
const int YELLOW_LED = 48;
const int BLUE_LED = 31;
const int BUTTON = 45;

const int standardDelay = 50;
const int longDelay = 125;

enum Color {
  RED, GREEN, YELLOW, BLUE
} lightColor = BLUE;

enum Mode {
  STATIC, BLINKING, SOS, DISCO1, DISCO2, OFF
} lightMode = OFF;

int sosIt = 0;

void setup() {
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  int b = readButton();
  if (b == 1) { // single click
    toggleLight();
  } else if (lightMode != OFF && b == 2) { // double click
    switchColor();
  } else if (lightMode != OFF && b == 3) { // click + hold
    switchLightMode();
  }
  updateLEDs();
}

void updateLEDs() {
  int ledPin = getLEDPin(lightColor);

  if (lightMode == STATIC) {
    turnLightsOff();
    digitalWrite(ledPin, HIGH);
  } else if (lightMode == BLINKING) {
    blink(ledPin, standardDelay);
  } else if (lightMode == SOS) {
    int sosPart = sosIt / 3;
    if (sosIt == 9) {
      sosIt = -1;
      delay(longDelay);
    } else if (sosPart % 2 == 0) {
      blink(ledPin, standardDelay);
    } else {
      blink(ledPin, longDelay);
    }
    sosIt++;
  } else if (lightMode == DISCO1) {
    blink(ledPin, standardDelay);
    switchColor();
  } else if (lightMode == DISCO2) {
    digitalWrite(ledPin, !digitalRead(ledPin));
    delay(100);
    switchColor();
  } else {
    turnLightsOff();
    lightColor = BLUE;
  }
}

void blink(int ledPin, int delayTime) {
  digitalWrite(ledPin, HIGH);
  delay(delayTime);
  digitalWrite(ledPin, LOW);
  delay(delayTime);
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
