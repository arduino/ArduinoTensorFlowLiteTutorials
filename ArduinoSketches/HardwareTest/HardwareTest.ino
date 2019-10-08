/*
  Hardware Test

  This example performs a basic hardware test of the board which includes
  testing the on-board IMU, LED and external button.

  When the button is pressed the on-board LED will turn on.

  The circuit:
  - Arduino Nano 33 BLE or Arduino Nano 33 BLE Sense board.
  - Button connected to pin 3 and GND.

  Created by Don Coleman, Sandeep Mistry

  This example code is in the public domain.
*/

#include <Arduino_LSM9DS1.h>

const int buttonPin = 3; 
const int ledPin = LED_BUILTIN;

int buttonState = LOW;  
int previousButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  //while (!Serial);
  Serial.println("Arduino ML Workshop Hardware Test");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the push button pin as an input with (internal) pullup:
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // read the state of the push button pin:
  buttonState = digitalRead(buttonPin);

  // HIGH and LOW are opposite because of we are using an internal pullup resistor.
  // LOW is pressed. HIGH is released.
  
  if (buttonState == LOW) {
    // Button is pressed, turn the LED on
    digitalWrite(ledPin, HIGH);
    if (buttonState != previousButtonState) {
      Serial.println("LED is ON");      
    }
  } else {
    // Button is released, turn the LED off
    digitalWrite(ledPin, LOW);
    if (buttonState != previousButtonState) {
      Serial.println("LED is OFF");      
    }
  }

  // save the previous state of the button since we only print
  // the LED status when the state changes
  previousButtonState = buttonState;
}
