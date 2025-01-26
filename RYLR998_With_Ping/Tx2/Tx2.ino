#include <SoftwareSerial.h>

// #define button 5

SoftwareSerial lora(2, 3);

String lora_RX_address = "1";   //enter Lora RX address

String incomingString;
void setup()
{
  // pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  lora.begin(9600);
  lora.setTimeout(1000);
}
int x=2;
void loop()
{

    if (lora.available()) {

    incomingString = lora.readString();
    Serial.println(incomingString);

    char dataArray[30]; 
    incomingString.toCharArray(dataArray,30);
    char* data = strtok(dataArray, ",");
    data = strtok(NULL, ",");
    data = strtok(NULL, ",");
    Serial.println(data);
    if (!strcmp(data,"OK")){
      lora.println("AT+SEND=" + lora_RX_address + ",18,HELLO WORLD FROM 3"); // AT+SEND=1,2,LO
      Serial.println("Sent");
      }
    else{
      Serial.println("Wrong Data");
    }
    }
    else
      Serial.println("Not Received");
  
  delay(1000);
}