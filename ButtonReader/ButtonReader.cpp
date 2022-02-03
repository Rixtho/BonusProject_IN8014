#include <Arduino.h>
#include <ButtonReader.h>

void ButtonReader::init(int _buttonPin) {
  buttonPin = _buttonPin;
  currentButtonState = LOW;
  previousButtonState = LOW;
  waitingForDoubleClick = false;
  ignoreNextRelease = false;
  downTime = -1;
  upTime = -1;
}

int ButtonReader::readButton() {
  int event = 0;
  currentButtonState = digitalRead(buttonPin);

  if (currentButtonState == HIGH && previousButtonState == LOW && (millis() - upTime) > debounce) {
    // button press
    downTime = millis();
    ignoreNextRelease = false;
  } else if (currentButtonState == LOW && previousButtonState == HIGH && (millis() - downTime) > debounce) {
    // button release
    if (!ignoreNextRelease) {
      upTime = millis();
      if (waitingForDoubleClick) {
        event = 2;
      }
      waitingForDoubleClick = !waitingForDoubleClick;
    }
  }

  if (currentButtonState == LOW && (millis() - upTime) >= doubleClickGap && waitingForDoubleClick) {
    // check if previous click can be registered as single click
    waitingForDoubleClick = false;
    event = 1;
  } else if (currentButtonState == HIGH && (millis() - downTime) >= holdTime) {
    // check for hold event
    downTime = millis(); // this way a longer hold will trigger a hold event every second
    waitingForDoubleClick = false;
    ignoreNextRelease = true;
    event = 3;
  }

  previousButtonState = currentButtonState;
  return event;
}
