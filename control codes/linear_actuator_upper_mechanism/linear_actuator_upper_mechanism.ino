// Stepper motor pins
#define stepPin 9
#define dirPin 8

#define limitSwitch1Pin 7  // Triggers stop + reverse after 5 seconds
#define limitSwitch2Pin 6  // Stops motor only while pressed

// states
bool moving = true;
bool direction = HIGH; // Start moving in one direction
bool limit1Handled = false;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(limitSwitch1Pin, INPUT_PULLUP);
  pinMode(limitSwitch2Pin, INPUT_PULLUP);

  digitalWrite(dirPin, direction);
}

void loop() {
  bool switch1Pressed = digitalRead(limitSwitch1Pin) == LOW;
  bool switch2Pressed = digitalRead(limitSwitch2Pin) == LOW;

  // If limit switch 2 is pressed, stop the motor (pause until released)
  if (switch2Pressed) {
    return; 
  }

  // Handle switch 1: stop and reverse after 5 seconds, but only once per press
  if (switch1Pressed && !limit1Handled) {
    moving = false;
    limit1Handled = true;

    delay(5000); // Wait for 5 seconds

    // Reverse direction
    direction = !direction;
    digitalWrite(dirPin, direction);
    moving = true;
  } else if (!switch1Pressed) {
    limit1Handled = false; // Reset when switch is released
  }

  if (moving) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(700);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(700);
  }
}
