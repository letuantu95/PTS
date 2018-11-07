/*SDA=D4,SCK=D5,MOSI=D7,MISO=D6,RST=D2
*/
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define SS_PIN D4
#define RST_PIN D2
#define interrupt D9
char readerID[]="cuachinh";//ten dau doc
byte UID[4];//id cua the

char ssid[] = "PSS_2";          //  your network SSID (name) 
char password[] = "pss201806";   // your network password
unsigned long start;
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

void setup() { 
  Serial.begin(9600);
  pinMode(D1,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D8,OUTPUT);
  digitalWrite(D1,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D8,LOW);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  ketnoiwifi();
  start = millis();
}

void loop() {
  if((millis() - start) > 50000){
     start = millis();
     Serial.println(start);
     digitalWrite(D1,LOW);Serial.println("dong cua");
  }
  if ( ! rfid.PICC_IsNewCardPresent()){
    return;
  }  
  else if ( ! rfid.PICC_ReadCardSerial()){
    return;
  }
  else{
    
    for (byte i = 0; i < 4; i++) {
      UID[i] = rfid.uid.uidByte[i];
    }
    digitalWrite(D8,HIGH);
    delay(500);
    digitalWrite(D8,LOW);
    Serial.println("UID: ");
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    sendUID();
  }
  //delay(1000);
}
void ketnoiwifi()
{
  WiFi.begin(ssid, password);
  while (1)
  {
    Serial.println(".");
    delay(100);
    if (WiFi.status() == WL_CONNECTED)
      break;
  }
  Serial.println("Da vao duoc internet");
}

void sendUID()
{
      Serial.println("connecting ....");
      String request ="http://carebook.vn/rfid/rfid";
      request += "/";
      request += String(readerID);
      request += "/";
      for(byte i=0;i<4;i++)
      {
        request += String(UID[i]);
      }
      Serial.println("Request: "+request); 
      HTTPClient http;  //Declare an object of class HTTPClient
      http.begin(request);  //Specify request destination
      int httpCode = http.GET(); //Send the request
      if (httpCode > 0) 
      { //Check the returning code
        String result = http.getString();   //Get the request response payload
        Serial.println("Result: "+ result);            //Print the response payload
        if (result=="active")
        {
          digitalWrite(D1,HIGH);
          Serial.println("mo cua");
        }
        else {
          digitalWrite(D1,LOW);
          Serial.println("dong cua");
              }
      } 
      else {
          digitalWrite(D1,LOW);
          Serial.println("dong cua");
            }  
      http.end(); 
}
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}



