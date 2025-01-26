#include<SoftwareSerial.h>

SoftwareSerial lora(2,3);


   
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  lora.begin(9600);
  delay(100);
  lora.println("AT+BAND=868000000");
  delay(100);
  lora.println("AT+PARAMETER=9,7,1,12");
  
  delay(1500);

}

void loop()
{
  lora.println("AT+SEND=1,5,HELLO");
  delay(1500);
}