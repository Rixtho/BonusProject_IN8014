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
  } else if (b == 3) {
    holdEvent();
  } else if (b == 4) {
    longHoldEvent();
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

void holdEvent() {
  digitalWrite(GREEN_LED, HIGH);
  delay(100);
  digitalWrite(GREEN_LED, LOW);
}
