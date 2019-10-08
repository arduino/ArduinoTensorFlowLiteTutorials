# Classifying IMU Data

1. Open __ArduinoSketches/IMU_Classifier/IMU_Classifier.ino__ in the Arduino IDE.
1. Switch to the model.h tab
1. Replace the contents of model.h with the version you downloaded from Colab
1. Upload the sketch: `Sketch -> Upload`
1. Open the Serial Monitor: `Tools -> Serial Monitor`
1. Press the button, and perform a gesture
1. The confidence of each gesture will be printed to the Serial Monitor (0 -> low confidence, 1 -> high confidence)

![screenshot with output of the imu classifier sketch](../images/arduino-classifier.png)

Next [Exercise 7: Gesture Controlled USB Emoji Keyboard](exercise7.md)
