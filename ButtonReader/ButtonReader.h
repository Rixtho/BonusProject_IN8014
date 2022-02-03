/**
*/
#ifndef ButtonReader_h
#define ButtonReader_h

#include <Arduino.h>

const int CLICK = 1;
const int DOUBLECLICK = 2;
const int HOLD = 3;

class ButtonReader {
public:
  void init(int _buttonPin);
  int readButton();

private:
  int buttonPin;

  boolean currentButtonState;
  boolean previousButtonState;
  boolean waitingForDoubleClick;
  boolean ignoreNextRelease;

  long downTime; // time when button was pressed
  long upTime; // time when button was released

  static const int debounce = 20; // debounce period to prevent flickering
  static const int doubleClickGap = 250; // max time between double click
  static const int holdTime = 1000; // min time for hold event
};

#endif
