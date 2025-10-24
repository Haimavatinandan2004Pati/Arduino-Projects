#include <Arduino.h>
// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

const int WAIT = 2;
const int READY = 3;
const int DETECTED = 4;
const int SENSOR_PIN = 5;
const int Tx_Pin = 12;

int prevVal = 0;
int sensorVal;

void setLEDStates(bool waitState, bool readyState, bool detectedState) {
    digitalWrite(WAIT, waitState);
    digitalWrite(READY, readyState);
    digitalWrite(DETECTED, detectedState);
}

void logWithTimestamp(const char* message) {
    unsigned long currentMillis = millis();
    Serial.print("[Time: ");
    Serial.print(currentMillis / 1000); // Convert milliseconds to seconds
    Serial.print("s] ");
    Serial.println(message);
}

 
void setup()
{
    pinMode(READY, OUTPUT);
    pinMode(WAIT, OUTPUT);
    pinMode(DETECTED, OUTPUT);
    pinMode(SENSOR_PIN, INPUT);

    setLEDStates(HIGH, LOW, LOW); // Initial state: Wait LED ON
    delay(60000);
    setLEDStates(LOW, HIGH, LOW); // Ready LED ON after delay

    // Initialize ASK Object
    if (!rf_driver.init())
    {
        Serial.println("ASK initialization failed");
        while (1); // Stay here if ASK initialization fails
    }
    
    // Initialize Serial Monitor
    Serial.begin(9600);
    Serial.println("Transmitter Ready");
}
 
void loop() {
    sensorVal = digitalRead(SENSOR_PIN);

    if (sensorVal == 0) {
        if (prevVal == 1) {
            logWithTimestamp("Recording stopped");
            setLEDStates(HIGH, LOW, LOW); // Wait LED ON
            delay(6000); // Blocking delay for 6 seconds
            setLEDStates(LOW, HIGH, LOW); // Ready LED ON
        } else {
            setLEDStates(LOW, HIGH, LOW); // Ready LED ON
        }
        prevVal = 0;
    } else if (sensorVal == 1) {
        if (prevVal == 0) {
            logWithTimestamp("Motion detected: Recording Started");
            SendMessage();
        }
        setLEDStates(LOW, LOW, HIGH); // Detected LED ON
        prevVal = 1;
    }
}

void SendMessage()
{ 
    setLEDStates(LOW, LOW, HIGH); // Detected LED ON
    const char *msg = "Motion detected";
    
    // Send message
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    Serial.println("Message Sent");
    
    delay(1000); // Wait 1 second before sending the next message
}
