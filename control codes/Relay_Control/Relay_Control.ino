const int limitSwitchPin = 8;  // Limit switch connected to pin 2
const int relayPin = 7;        // Relay module connected to pin 8

bool relayState = false;       // Stores the current state of the relay
bool lastSwitchState = HIGH;   // Stores the last state of the switch

void setup() {
  pinMode(limitSwitchPin, INPUT_PULLUP);  // Use internal pull-up resistor
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, relayState);  // Initialize relay state
}

void loop() {
  bool currentSwitchState = digitalRead(limitSwitchPin);

  // Detect falling edge (press)
  if (lastSwitchState == HIGH && currentSwitchState == LOW) {
    relayState = !relayState;  // Toggle relay state
    digitalWrite(relayPin, relayState);
    delay(50); // Debounce delay
  }

  lastSwitchState = currentSwitchState; // Update switch state
}
