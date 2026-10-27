// Angry Piggies joystick controller.
// Sends "x,y,button" lines over USB serial about 50 times a second.
// x and y go from -100 to 100 (0 = centre), button is 1 while pressed.
//
// Wiring (5-pin KY-023 / PS2-style joystick module, plus an optional push button):
//   GND -> GND    +5V -> 5V    VRx -> A0    VRy -> A2    SW -> D2
//   Push button on the breadboard -> D3 (with its own resistor)
// Pressing the stick or the push button both count as "fire".

const int PIN_X = A0;
const int PIN_Y = A2;
const int PIN_STICK_PRESS = 2;  // joystick SW: connects to GND when pressed
const int PIN_BUTTON = 3;       // breadboard push button

// What pin 3 reads while the push button is held. Wired 5V -> button -> pin 3 with the
// resistor to GND (pull-down), that's HIGH. If the Serial Monitor's third number sits at 1
// and drops to 0 when you press, your resistor goes to 5V instead: change this to LOW.
const int BUTTON_PRESSED = HIGH;

// Open Tools > Serial Monitor (115200 baud): pushing the stick right should make x
// positive and pushing it down (toward you) should make y positive. If not, flip these.
// (If pushing right changes the second number instead, swap PIN_X and PIN_Y.)
const bool INVERT_X = false;
const bool INVERT_Y = false;

// Raw readings this close to the centre count as "stick not touched"
const int DEADZONE = 40;

int centerX;
int centerY;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_STICK_PRESS, INPUT_PULLUP);  // the module has no resistor of its own
  pinMode(PIN_BUTTON, INPUT);              // the breadboard resistor holds it steady
  // Leave the stick alone while the board starts: this reading becomes the centre
  centerX = analogRead(PIN_X);
  centerY = analogRead(PIN_Y);
}

// Raw 0..1023 reading -> -100..100 around the measured centre
int readAxis(int pin, int center, bool invert) {
  int offset = analogRead(pin) - center;
  if (abs(offset) < DEADZONE) return 0;
  long range = offset > 0 ? 1023 - center : center;
  int value = constrain(offset * 100L / range, -100, 100);
  return invert ? -value : value;
}

void loop() {
  int x = readAxis(PIN_X, centerX, INVERT_X);
  int y = readAxis(PIN_Y, centerY, INVERT_Y);
  bool stickPressed = digitalRead(PIN_STICK_PRESS) == LOW;
  bool buttonPressed = digitalRead(PIN_BUTTON) == BUTTON_PRESSED;
  int pressed = stickPressed || buttonPressed ? 1 : 0;

  Serial.print(x);
  Serial.print(',');
  Serial.print(y);
  Serial.print(',');
  Serial.println(pressed);

  delay(20);
}
