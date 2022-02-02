int debounce = 20; // debounce period to prevent flickering
int doubleClickGap = 250; // max time between double click
int holdTime = 1000; // min time for hold event

boolean currentButtonState = HIGH;
boolean previousButtonState = HIGH;

boolean waitingForDoubleClick = false;
boolean ignoreNextRelease = false;

long downTime = -1; // time when button was pressed
long upTime = -1; // time when button was released

int readButton() {
  int event = 0;
  // return value 1, for single click
  //              2, for double click
  //              3, for click + hold
  //              0, if nothing happened

  currentButtonState = digitalRead(BUTTON);

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

  // check if click can be registered as single click
  if (currentButtonState == LOW && (millis() - upTime) >= doubleClickGap && waitingForDoubleClick) {
    waitingForDoubleClick = false;
    event = 1;
  }

  // check for hold event
  if (currentButtonState == HIGH && (millis() - downTime) >= holdTime) {
    downTime = millis(); // this way a longer hold will trigger a hold event every second
    waitingForDoubleClick = false;
    ignoreNextRelease = true;
    event = 3;
  }

  previousButtonState = currentButtonState;
  return event;
}
