/*SDA=D4,SCK=D5,MOSI=D7,MISO=D6,RST=D2
*/
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#define SS_PIN D4
#define RST_PIN D2
char readerID[]="cuachinh";//ten dau doc
byte UID[4];//id cua the

char ssid[] = "PSS";          //  your network SSID (name) 
char password[] = "pss201806";   // your network password
WiFiClient client;
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

void setup() { 
  Serial.begin(9600);
  pinMode(D1,OUTPUT);
  digitalWrite(D1,LOW);
  pinMode(D8,OUTPUT);
  digitalWrite(D8,LOW);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  ketnoiwifi();
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
  return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;
    for (byte i = 0; i < 4; i++) {
      UID[i] = rfid.uid.uidByte[i];
    }
    digitalWrite(D8,HIGH);
    delay(1000);
    digitalWrite(D8,LOW);
    Serial.println();
    Serial.print(F("UID: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    sendUID();
    readreq();
    delay(1000);
  //kiểm tra internet
  // khi client da ket noi thanh cong va san sang thi thuc hien doc tin hieu tu server gui ve
  //va in ra kien tra thanh cong- sau do thuc hien ham bat/tat thiet bi
    if (client) {
    if (client.available()) {
    char c = client.read();
    Serial.print(c);
    }
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for(;;)
      ;
    }
    }
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
  if (client.connect("carebook.vn", 80)) {
      Serial.println("connected");
      // Make a HTTP request:
      String request ="GET /rfid/rfid";
      request += "/";
      request += String(readerID);
      request += "/";
      
      for(byte i=0;i<4;i++)
      {
        request += String(UID[i]);
      }
      request += " HTTP/1.0";
      client.println(request);
      client.println();     
    }
  if (client.connected()) {
      client.stop();  // DISCONNECT FROM THE SERVER
  }
}
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}

void readreq()
{
  String str;
  int from = str.indexOf('?');
  int to = str.indexOf(' ', from);
  String GET = str.substring(from, to);
  if (GET=="active")
  {
    digitalWrite(D1,HIGH);
    Serial.println("mo cua");
  }
  else {digitalWrite(D1,LOW);Serial.println("dong cua");}
}

//void readreq1()
//{
//  String req = client.readStringUntil('\r');
//  if (req.indexOf("5b55513977c82c8d26ab56e1")==true){
//   Serial.println("mo cua");
//  }
//}

//void docthe()
//{
//  while ( ! rfid.PICC_IsNewCardPresent());
//  //if ( ! rfid.PICC_ReadCardSerial())
//    //return;
//    Serial.print("asfla ");
//    for (byte i = 0; i < 4; i++) {
//      UID[i] = rfid.uid.uidByte[i];
//    }
//    Serial.print(F("UID: "));
//    printDec(rfid.uid.uidByte, rfid.uid.size);
//    Serial.println();
//    // Halt PICC
//    rfid.PICC_HaltA();
//    // Stop encryption on PCD
//    rfid.PCD_StopCrypto1();
//}
