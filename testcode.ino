#include <Arduino.h>
#include <PS4Controller.h> // Library for PS4 controller

// Define the pins for MDD10A motor driver
#define DIR1_PIN 4
#define DIR2_PIN 5
#define PWM1_PIN 6
#define PWM2_PIN 7

// Initialize the PS4 controller
PS4Controller ps4;

void setup() {
  // Initialize PS4 controller
  ps4.begin("1a:2b:3c:01:01:01");
    Serial.println("Ready.");

  // Set up MDD10A pins as outputs
  pinMode(DIR1_PIN, OUTPUT);
  pinMode(DIR2_PIN, OUTPUT);
  pinMode(PWM1_PIN, OUTPUT);
  pinMode(PWM2_PIN, OUTPUT);
}

void loop() {
  // Read PS4 controller inputs
  ps4.readUSB(); // Use readUSB if connected via USB, otherwise use readBluetooth for Bluetooth connection

  // Drive the soccer bot based on controller inputs
  float leftSpeed = ps4.LStickY() * 255; // Map controller input to motor speed
  float rightSpeed = ps4.RStickY() * 255;

  // Control the left motor
  if (leftSpeed < 0) {
    digitalWrite(DIR1_PIN, LOW); // Set motor direction to backward
    analogWrite(PWM1_PIN, abs(leftSpeed));
  } else {
    digitalWrite(DIR1_PIN, HIGH); // Set motor direction to forward
    analogWrite(PWM1_PIN, abs(leftSpeed));
  }

  // Control the right motor
  if (rightSpeed < 0) {
    digitalWrite(DIR2_PIN, LOW); // Set motor direction to backward
    analogWrite(PWM2_PIN, abs(rightSpeed));
  } else {
    digitalWrite(DIR2_PIN, HIGH); // Set motor direction to forward
    analogWrite(PWM2_PIN, abs(rightSpeed));
  }
}
