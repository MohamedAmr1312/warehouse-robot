// define motor, relay and limit switchs
#define stepPin 9
#define dirPin 8


#define limitSwitch1Pin 7  // stepper control and relay toggle (for pump)
#define limitSwitch2Pin 6  // Stops motor only while pressed
#define relayPin 5         // Relay module (for pump)

// States
bool moving = true;
bool direction = HIGH;
bool limit1Handled = false;

bool relayState = false;
bool lastSwitch1State = HIGH;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(limitSwitch1Pin, INPUT_PULLUP);
  pinMode(limitSwitch2Pin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);

  digitalWrite(dirPin, direction);
  digitalWrite(relayPin, relayState);
}

void loop() {
  bool switch1State = digitalRead(limitSwitch1Pin);
  bool switch2State = digitalRead(limitSwitch2Pin);

  // Toggle relay on falling edge 
  if (lastSwitch1State == HIGH && switch1State == LOW) {
    relayState = !relayState;
    digitalWrite(relayPin, relayState);
    delay(50); // Debounce
  }
  lastSwitch1State = switch1State;

  
  if (switch2State == LOW) return;   // Stop motor while limit switch 2 is pressed

  // switch 1: stop and reverse after 5 seconds, once per press
  if (switch1State == LOW && !limit1Handled) {
    moving = false;
    limit1Handled = true;

    delay(5000); // Wait before reversing

    direction = !direction;
    digitalWrite(dirPin, direction);
    moving = true;
  } else if (switch1State == HIGH) {
    limit1Handled = false; // Reset when switch is released
  }

  if (moving) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(700);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(700);
  }
}
