#include <SoftwareSerial.h>

// #define LED 13

String incomingString;

SoftwareSerial lora(2,3);
String lora_RX_address = "2";   //enter Lora RX address
void setup()
{
  // pinMode(LED, OUTPUT);
  Serial.begin(9600);
  lora.begin(9600);
  lora.setTimeout(1000);
}
String channel;
void loop()
{

    sendPing(2);
    delay(500);

    receiveData(2);

    delay(2500);
    
    sendPing(3);
    delay(500);

    receiveData(3);
    delay(2500);
    // delay(1000);
}

void sendPing(int id)
{
  Serial.println("Sent "+String(id));
  lora.println("AT+SEND=" + String(id) + ",2,OK"); // AT+SEND=1,2,LO

}

void receiveData(int id)
{
    unsigned long startTime = millis();
    while (millis() - startTime < 2000) { // Wait up to 2 seconds
        if (lora.available()) {
            incomingString = lora.readString();
            Serial.println("Received: " + incomingString);

            // Check if the message format is valid
            if (incomingString.startsWith("+RCV=")) {
                // Extract sender ID
                int senderID = incomingString.substring(5, incomingString.indexOf(',')).toInt();

                if (1) {
                    // Match found, process the message
                    char dataArray[50];
                    incomingString.toCharArray(dataArray, 50);
                    char* data = strtok(dataArray, ","); // Skip "+RCV="
                    data = strtok(NULL, ",");           // Skip sender ID
                    data = strtok(NULL, ",");           // Extract actual message
                    if (data) {
                        Serial.println("Message from " + String(id) + ": " + String(data));
                    } else {
                        Serial.println("No valid message data found.");
                    }
                    return; // Exit the function after processing the intended message
                } else {
                    // Ignore messages not meant for the current `id`
                    Serial.println("Ignored message from ID: " + String(senderID));
                }
            } else {
                Serial.println("Invalid message format: " + incomingString);
            }
        }
    }
    Serial.println("Timeout");
}
