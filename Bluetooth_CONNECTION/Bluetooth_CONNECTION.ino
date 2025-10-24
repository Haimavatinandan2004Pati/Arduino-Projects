const int BUTTON_PIN = 5;      // Pushbutton connected to D5
const int BUZZER_PIN = 2;      // Buzzer connected to D2
const int LED_GREEN_PIN = 3;   // Green LED (D3)
const int LED_RED_PIN = 4;     // Red LED (D2)
const int IR_PIN = 7;         // IR Sensor (D7)

int buttonState;
int lastButtonState = HIGH;
bool countdownRunning = false;

int countdownTime = 60;                   // Countdown start time (in seconds)
unsigned long previousMillis = 0;
unsigned long interval = 1000;            // Initial interval (1 sec)
int speedMultiplier = 1;                  // Doubles each press during countdown
const int MAX_MULTIPLIER = 16;             // Max speed 8x
const unsigned long DEBOUNCE_DELAY = 200; // Avoid rapid re-triggers
unsigned long lastPressTime = 0;
int IR_value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);

  // Initially everything OFF
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_RED_PIN, LOW);

  Serial.println("--- Press Button to Start Countdown ---");
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);
  unsigned long currentMillis = millis();
  
  // --- Button press detection with debounce ---
  if (buttonState == LOW && lastButtonState == HIGH && (currentMillis - lastPressTime) > DEBOUNCE_DELAY) {
    lastPressTime = currentMillis;

    if (!countdownRunning) {
      // Start the countdown
      countdownRunning = true;
      countdownTime = 60;
      interval = 1000;
      speedMultiplier = 1;
      Serial.println("Countdown Started!");
      digitalWrite(LED_GREEN_PIN, LOW); // Green off while counting
      previousMillis = millis();
    } else {
      // Accelerate the countdown
      if (speedMultiplier < MAX_MULTIPLIER) {
        speedMultiplier *= 2;
        interval = 1000 / speedMultiplier;
        Serial.print("Speed Increased! New rate: ");
        Serial.print(speedMultiplier);
        Serial.println("x");
      } else {
        Serial.println("Maximum speed reached!");
      }
    }
  }

  lastButtonState = buttonState;

  // --- Countdown logic ---
  if (countdownRunning) {
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      // Red blink + beep per count
      digitalWrite(LED_RED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);

      Serial.print("Time remaining: ");
      Serial.println(countdownTime);

      countdownTime--;

      // End of countdown
      if ((countdownTime < 0) && (Serial.available() > 0)){ 
        Serial.println("*** Countdown Finished! ***");
        digitalWrite(LED_GREEN_PIN, HIGH); // Green ON steady
        digitalWrite(LED_RED_PIN, LOW);
        digitalWrite(BUZZER_PIN, LOW);
        countdownRunning = false;
      }
    }
  }
}

