#include<SoftwareSerial.h>

SoftwareSerial lora(2,3);

void setup()
{
  Serial.begin(9600);
  lora.begin(9600);
  delay(100);
  lora.println("AT+BAND=868000000");
  delay(100);
  lora.print("AT+PARAMETER=9,7,1,12");
  delay(100);
  Serial.println("LoRa Setup Completed");
}

void loop()
{ 
  Serial.println(lora.readString());
  delay(500);
}