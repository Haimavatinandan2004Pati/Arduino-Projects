// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
 
void setup()
{
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
 
void loop()
{
    const char *msg = "Welcome to the Workshop!";
    
    // Send message
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    Serial.println("Message Sent");
    
    delay(1000); // Wait 1 second before sending the next message
}
