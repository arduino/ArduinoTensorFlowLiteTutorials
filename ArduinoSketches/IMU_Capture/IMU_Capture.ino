/*
  IMU Capture

  This example uses the on-board IMU to start reading acceleration and gyroscope 
  data from on-board IMU and prints it to the Serial Monitor for one second
  when the button is pressed.

  You can also use the Serial Plotter to graph the data.

  The circuit:
  - Arduino Nano 33 BLE or Arduino Nano 33 BLE Sense board.
  - Button connected to pin 3 and GND.

  Created by Don Coleman, Sandeep Mistry

  This example code is in the public domain.
*/

#include <Arduino_LSM9DS1.h>

const int buttonPin = 3;     // the number of the pushbutton pin
const int numSamples = 119;

int previousButtonState = HIGH;
int samplesRead = numSamples;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // initialize the pushbutton pin as an input with (internal) pullup:
  pinMode(buttonPin, INPUT_PULLUP);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // print the header
  Serial.println("aX,aY,aZ,gX,gY,gZ");
}

void loop() {
  // read the state of the push button pin:
  int buttonState = digitalRead(buttonPin);

  // compare the button state to the previous state
  // to see if it has changed
  if (buttonState != previousButtonState) {
    if (buttonState == LOW) {
      if (samplesRead == numSamples) {
        // pressed
        samplesRead = 0;
      }
    } else {
      // released
    }

    // store the state as the previous state, for the next loop
    previousButtonState = buttonState;
  }

  // check if the all the required samples have been read since 
  // the last time the button has been pressed
  if (samplesRead < numSamples) {
    // check if both new acceleration and gyroscope data is
    // available
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
      float aX, aY, aZ, gX, gY, gZ;

      // read the acceleration and gyroscope data
      IMU.readAcceleration(aX, aY, aZ);
      IMU.readGyroscope(gX, gY, gZ);

      samplesRead++;

      // print the data in CSV format
      Serial.print(aX, 3);
      Serial.print(',');
      Serial.print(aY, 3);
      Serial.print(',');
      Serial.print(aZ, 3);
      Serial.print(',');
      Serial.print(gX, 3);
      Serial.print(',');
      Serial.print(gY, 3);
      Serial.print(',');
      Serial.print(gZ, 3);
      Serial.println();

      if (samplesRead == numSamples) {
        // add an empty line if it's the last sample
        Serial.println();
      }
    }
  }
}
