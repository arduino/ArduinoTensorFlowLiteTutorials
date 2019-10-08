/*
  Emoji Button

  This example sends an emoji character over USB HID when the button is pressed.

  Note: Only macOS and Linux as supported at this time, and the use of
        #define is generally discouraged in Arduino examples

  The circuit:
  - Arduino Nano 33 BLE or Arduino Nano 33 BLE Sense board.
  - Button connected to pin 3 and GND.

  Created by Don Coleman, Sandeep Mistry

  This example code is in the public domain.
*/

#include <PluggableUSBHID.h>
#include <USBKeyboard.h>

// Select an OS:
//#define MACOS // You'll need to enable and select the unicode keyboard: System Preferences -> Input Sources -> + -> Others -> Unicode Hex Input
//#define LINUX

#if !defined(MACOS) && !defined(LINUX)
#error "Please select an OS!"
#endif

// use table: https://apps.timwhitlock.info/emoji/tables/unicode
const int bicep = 0x1f4aa;
const int punch = 0x1f44a;

const int buttonPin = 3;

USBKeyboard keyboard;

int previousButtonState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState != previousButtonState) {
    if (buttonState == LOW) {
      // pressed
      sentUtf8(bicep);
    } else {
      // released
    }

    previousButtonState = buttonState;
  }
}

void sentUtf8(unsigned long c) {
  String s;

#if defined(MACOS)
  // https://apple.stackexchange.com/questions/183045/how-can-i-type-unicode-characters-without-using-the-mouse

  s = String(utf8ToUtf16(c), HEX);

  for (int i = 0; i < s.length(); i++) {
    keyboard.key_code(s[i], KEY_ALT);
  }
#elif defined(LINUX)
  s = String(c, HEX);

  keyboard.key_code('u', KEY_CTRL | KEY_SHIFT);

  for (int i = 0; i < s.length(); i++) {
    keyboard.key_code(s[i]);
  }
#endif
  keyboard.key_code(' ');
}

// based on https://stackoverflow.com/a/6240819/2020087
unsigned long utf8ToUtf16(unsigned long in) {
  unsigned long result;

  in -= 0x10000;

  result |= (in & 0x3ff);
  result |= (in << 6) & 0x03ff0000;
  result |= 0xd800dc00;

  return result;
}
