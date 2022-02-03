#include <ButtonReader.h>

const int RED_LED = 30;
const int GREEN_LED = 31;
const int YELLOW_LED = 32;
const int BLUE_LED = 33;
const int BUTTON = 2;

ButtonReader buttonReader;

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  buttonReader.init(BUTTON);
}

void loop() {
  int clickEvent = buttonReader.readButton();
  if (clickEvent == CLICK) {
    digitalWrite(BLUE_LED, !digitalRead(BLUE_LED));
  } else if (clickEvent == DOUBLECLICK) {
    digitalWrite(RED_LED, !digitalRead(RED_LED));
  } else if (clickEvent == HOLD) {
    digitalWrite(GREEN_LED, !digitalRead(GREEN_LED));
  }
}
