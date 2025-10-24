// This constant controls the pin number for the built-in LED (usually pin 13 on Uno/Nano)
const int LED_PIN = 13; 

// The setup routine runs once when you press reset or power the board
void setup() {
  // Initialize digital pin LED_PIN as an output.
  pinMode(LED_PIN, OUTPUT);
}

// The loop routine runs over and over again forever
void loop() {
  // Turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_PIN, HIGH);   
  delay(1000);                      // Wait for a second (1000 milliseconds)

  // Turn the LED off by making the voltage LOW
  digitalWrite(LED_PIN, LOW);    
  delay(1000);                      // Wait for a second
}
