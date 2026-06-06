#include <Servo.h>

// Pin assignments
const int buttonPin = 6;
const int buzzerPin = 7;
const int ledPin = 8;
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 11;

// System states and variables
Servo Servo1;
long duration;
int distance;
int lastDistance = 0;
unsigned long lastMovementTime = 0;
bool emergencyMode = false;
unsigned long lastServoMove = 0;
bool servoDirection = true; // true = increasing, false = decreasing

// Timing constants for demo
const unsigned long INITIAL_ALERT_TIME = 5000;   // 5 seconds until LED alert
const unsigned long NUDGE_TIME = 10000;          // 10 seconds until servo nudge
const unsigned long EMERGENCY_TIME = 15000;      // 15 seconds until full emergency
const int DISTANCE_THRESHOLD = 5;                // 5 cm movement threshold

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);

  Servo1.attach(servoPin);
  Servo1.write(0); // Initial position

  Serial.begin(9600);
  Serial.println("Fall Detection System Initialized");

  lastDistance = getDistance();
  lastMovementTime = millis();
}

void loop() {
  distance = getDistance();

  Serial.print("Distance: ");
  Serial.println(distance);

  // Scenario 1: Manual emergency button press
  if (digitalRead(buttonPin) == HIGH && !emergencyMode) {
    triggerEmergency("Manual emergency triggered");
  }

  // Scenario 2: Automatic inactivity / unconsciousness detection
  if (!emergencyMode) {
    checkForUnconscious();
  }

  // Continue emergency behaviour if in emergency mode
  if (emergencyMode) {
    updateEmergencyState();
  }

  // Reset system if button is pressed during emergency
  if (emergencyMode && digitalRead(buttonPin) == HIGH) {
    delay(50); // Simple debounce
    resetSystem();
  }

  delay(100); // Stabilise readings
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void checkForUnconscious() {
  // Check for movement using distance difference
  if (abs(distance - lastDistance) > DISTANCE_THRESHOLD) {
    lastMovementTime = millis();
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    Servo1.write(0);
    Serial.println("Movement detected");
  }

  unsigned long timeSinceMovement = millis() - lastMovementTime;

  // Stage 1: LED warning
  if (timeSinceMovement > INITIAL_ALERT_TIME && timeSinceMovement < NUDGE_TIME) {
    blinkLED();
    Serial.println("Stage 1: LED Warning");
  }

  // Stage 2: Servo nudge
  else if (timeSinceMovement > NUDGE_TIME && timeSinceMovement < EMERGENCY_TIME) {
    blinkLED();
    nudgeElderly();
    Serial.println("Stage 2: Nudging");
  }

  // Stage 3: Full emergency
  else if (timeSinceMovement > EMERGENCY_TIME) {
    triggerEmergency("Unconscious state detected");
  }

  lastDistance = distance;
}

void triggerEmergency(String message) {
  emergencyMode = true;
  Serial.println(message);

  digitalWrite(ledPin, HIGH);
  tone(buzzerPin, 1000);
  lastServoMove = millis();
}

void updateEmergencyState() {
  digitalWrite(ledPin, HIGH);
  tone(buzzerPin, 1000);

  // Continuously move servo back and forth
  unsigned long currentTime = millis();

  if (currentTime - lastServoMove >= 1000) {
    if (servoDirection) {
      Servo1.write(90);
    } else {
      Servo1.write(0);
    }

    servoDirection = !servoDirection;
    lastServoMove = currentTime;
  }
}

void blinkLED() {
  if ((millis() % 500) < 250) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void nudgeElderly() {
  static unsigned long lastNudgeTime = 0;

  if (millis() - lastNudgeTime >= 1000) {
    if (Servo1.read() == 0) {
      Servo1.write(45); // Gentle nudge
    } else {
      Servo1.write(0);  // Return position
    }

    lastNudgeTime = millis();
  }
}

void resetSystem() {
  emergencyMode = false;
  digitalWrite(ledPin, LOW);
  noTone(buzzerPin);
  Servo1.write(0);
  lastMovementTime = millis();
  servoDirection = true;

  Serial.println("System Reset");
}
