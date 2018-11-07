
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
#define interrupt D3
#define SS_PIN D4
#define RST_PIN D2
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
unsigned long start;
byte UID[4];
void ngat()
{
  Serial.println("ad");
  digitalWrite(D1,HIGH);
  delay(1000);
  digitalWrite(D1,LOW);
  delay(1000);
}
void setup() {
  Serial.begin(9600);
  //attachInterrupt(interrupt, ngat, FALLING);
  SPI.begin();
  rfid.PCD_Init(); // Init MFRC522 
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  Serial.println("dnfsdfk");
  pinMode(D1,OUTPUT);
  pinMode(D3, INPUT_PULLUP);
  start = millis();
}

void loop() {
  while(digitalRead(D3)==0)
  {
    ngat();
  }
    if((millis() - start) > 60000){
     start = millis();
     Serial.println(start);
     if(digitalRead(D1)==1){
      Serial.println(digitalRead(D1));
     //delay(10000);
     digitalWrite(D1,LOW);Serial.println("dong cua");
     }
  }
  if ( ! rfid.PICC_IsNewCardPresent()){
    return;
  }  
  else if ( ! rfid.PICC_ReadCardSerial()){
    return;
  }
  else{ 
    Serial.println("ew");
    for (byte i = 0; i < 4; i++) {
      UID[i] = rfid.uid.uidByte[i];
    }
    delay(1000);
  for(byte i=0;i<4;i++)
  {
    Serial.print(UID[i]);
    Serial.print(" ");
  }
  digitalWrite(D1,HIGH);
  }
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
