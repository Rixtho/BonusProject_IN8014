const int RED_LED = 40;
const int GREEN_LED = 22;
const int YELLOW_LED = 48;
const int BLUE_LED = 31;
const int BUTTON = 45;

enum light {
  RED, GREEN, YELLOW, BLUE, OFF
} lightColor;

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
  if (b == 1) {
    clickEvent();
  } else if (b == 2) {
    doubleClickEvent();
  }
}

void clickEvent() {
  digitalWrite(RED_LED, HIGH);
  delay(100);
  digitalWrite(RED_LED, LOW);
}

void doubleClickEvent() {
  digitalWrite(BLUE_LED, HIGH);
  delay(100);
  digitalWrite(BLUE_LED, LOW);
}

//=========================================================
// click handling

int debounce = 20; // debounce period to prevent flickering
int doubleClickGap = 250; // max time between double click

boolean currentButtonState = HIGH;
boolean previousButtonState = HIGH;

long downTime = -1; // time the button was pressed
long upTime = -1; // time the button was released

int readButton() {
  int event = 0;
  // we return  1, for normal click
  //            2, for double click
  //            0, else

  currentButtonState = digitalRead(BUTTON);

  if (currentButtonState == HIGH && previousButtonState == LOW && (millis() - upTime) > debounce) {
    // button press
    downTime = millis();
    if ((millis() - upTime) < doubleClickGap) {
      clickCounter++;
    } else {
      clickCounter = 1;
    }
  } else if (currentButtonState == LOW && previousButtonState == HIGH && (millis() - downTime) > debounce) {
    // button release
    upTime = millis();
    event = clickCounter;
  }
  Serial.println(clickCounter);

  // check for normal or double click
  if (currentButtonState == LOW && (millis() - upTime) >= doubleClickGap && event != 0) {
    clickCounter = 0;
    event = 1;
  }

  previousButtonState = currentButtonState;
  return event;
}
