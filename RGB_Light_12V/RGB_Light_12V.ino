// RGB Common Anode LED (12V) controlled by transistors on D2, D3, D4
// LOW = ON, HIGH = OFF (because of common anode)

#define RED_PIN   2
#define GREEN_PIN 3
#define BLUE_PIN  4

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Turn off all colors initially
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
}

void loop() {
  setColor(255, 0, 0);   // Red
  delay(1000);
  setColor(0, 255, 0);   // Green
  delay(1000);
  setColor(0, 0, 255);   // Blue
  delay(1000);
  setColor(255, 255, 0); // Yellow
  delay(1000);
  setColor(0, 255, 255); // Cyan
  delay(1000);
  setColor(255, 0, 255); // Magenta
  delay(1000);
  setColor(0, 0, 0); // White
  delay(1000);
}

void setColor(uint8_t r, uint8_t g, uint8_t b) {
  // Since common anode, invert the logic
  analogWrite(RED_PIN,   255 - r);
  analogWrite(GREEN_PIN, 255 - g);
  analogWrite(BLUE_PIN,  255 - b);
}
