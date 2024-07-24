#include <ESP32Servo.h>

// Driving Pins
const int FORWARD_PIN = 33; // IN3
const int BACKWARD_PIN = 32; // IN4
const int SPEED_PIN = 14; // ENA
const int STEERING_PIN = 27; // Servo

// Create the servo
Servo steeringServo;

// Speed PWM Channel
const int SPEED_CHANNEL = 6;

// Initializes eveything for driving
void initDrive() {
  // Set driving direction pins
  pinMode(FORWARD_PIN, OUTPUT);
  pinMode(BACKWARD_PIN, OUTPUT);
  
  // Set speed channel pin
  ledcSetup(SPEED_CHANNEL, 5000, 8);
  pinMode(SPEED_PIN, OUTPUT);
  ledcAttachPin(SPEED_PIN, SPEED_CHANNEL);
  
  // Set servo pin
  steeringServo.attach(STEERING_PIN);
}

// Drives the rear wheels at specified speed (-255 to 255)
void drive(int speed) {
  // Drive forward
  if (speed > 0){
    digitalWrite(FORWARD_PIN, HIGH);
    digitalWrite(BACKWARD_PIN, LOW);
    ledcWrite(SPEED_CHANNEL, speed);
  // Drive backward
  } else if (speed < 0) {
    digitalWrite(FORWARD_PIN, LOW);
    digitalWrite(BACKWARD_PIN, HIGH);
    ledcWrite(SPEED_CHANNEL, -speed);
  // Stop
  } else if (speed == 0) {
    digitalWrite(FORWARD_PIN, LOW);
    digitalWrite(BACKWARD_PIN, LOW);
    ledcWrite(SPEED_CHANNEL, 0);
  }
}

// Steers the front wheels at the specified angle (20 to 160)
void steer(int angle) {
  angle = constrain(angle, 20, 160);
  steeringServo.write(angle);
}