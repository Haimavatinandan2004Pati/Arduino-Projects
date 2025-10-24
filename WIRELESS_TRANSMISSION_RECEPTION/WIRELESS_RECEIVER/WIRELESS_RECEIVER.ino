// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
 
void setup()
{
    // Initialize ASK Object
    if (!rf_driver.init()) {
        Serial.println("ASK initialization failed");
        while (1); // Halt if initialization fails
    }
    
    // Setup Serial Monitor
    Serial.begin(9600);
    Serial.println("Receiver Ready");
}
 
void loop()
{
    // Set buffer to size of expected message
    uint8_t buf[24]; //size of the message to be received
    uint8_t buflen = sizeof(buf);
    
    // Check if a packet is received
    if (rf_driver.recv(buf, &buflen)) {
        // Message received with valid checksum
        Serial.print("Message Received: ");
        Serial.println((char*)buf);
    } else {
        // No message received
        delay(500); // Add delay to reduce Serial Monitor spam
    }
}
