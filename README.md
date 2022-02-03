# Smart Light Switch

## Motivation

Light switches have been doing the same thing for years and years.
Pressing the switch turns the light either on or off.
Our ButtonReader helps you bring your light switch to the next level and implement different actions for
- a single click,
- a double click, or
- a click and hold.

## Installation

1. Download the library [here](resources/ButtonReader.zip).
2. Open your Arduino IDE and go to **Sketch | Include Library** and select **Add .ZIP Library...**
3. Select the downloaded folder.
4. Restart the Arduino IDE.

You're good to go!

## Getting Started

1. In order to use the ButtonReader you must add following statement to your sketch: `#include <ButtonReader.h>`
2. Then you have to declare a new variable of this class: `ButtonReader buttonReader;`
3. To initialise this variable add the following statement to `setup()`: `buttonReader.init(buttonPin)`. <br/>
`buttonPin` should be a digital pin to which you connected a switch.
An example circuit can be found in our [examples folder](ButtonReader/examples).
4. In `loop()` call `buttonReader.readButton()` to read the button.
5. Define different actions for the possible events `CLICK`, `DOUBLECLICK` and `HOLD`.
You don't have to define an action for every event, if you don't want to use that click event.

Let's have a look at our demo code:
```cpp
#include <ButtonReader.h>

const int RED_LED = 30;
const int GREEN_LED = 31;
const int BLUE_LED = 33;
const int BUTTON = 2;

ButtonReader buttonReader;

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
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
```

This program turns the blue LED on or off when we click normally.
It turns the red LED on or off when we double click, and turns the green LED on or off when we hold the button.

This means we just utilised one button to control three different lights. :)

### Tips
- `readButton()` is a polling function, i.e. this ButtonReader works better, the more often it can run.
- For two clicks to be recognised as a double click, they must be closer than 250 milliseconds apart.
This number is currently not adjustable.
Consequently, less than 250 milliseconds should elapse between two calls of `readButton()` for a double click to be recognised.
- The duration for a hold event is one second. Currently this number is not adjustable.
Holding the button for more than one second will trigger the hold event correspondingly often in succession.
E.g. clicking the button for four seconds will trigger four hold events.
