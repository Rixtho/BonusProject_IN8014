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
