#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 
// Init array that will store new NUID 
int nuidPICC[4];
int sothe=2, tep=0,k=0;
int mang[][4]={{65, 246 ,147 ,46},{54, 44, 200, 115},};
int pin=3;
bool x=true;
bool isSame(int *key, int *serial)
{
    for (int i = 0; i < 4; i++) {
      if (key[i] != serial[i])
      { 
        return false; 
      }
    }   
    return true;
}
bool isAuthorized()
{
    for(int k = 0; k<=sothe; k++)//vòng lập tương ứng với số thẻ.
    {
      if(isSame(nuidPICC, mang[k]))
        return true;
    }
   return false;
}
void nhapthe()
{
  Serial.println("awd");
  sothe++;
//  while(1)
//  {
//    if ( ! rfid.PICC_IsNewCardPresent())
//    return;
//  // Verify if the NUID has been readed
//  if ( ! rfid.PICC_ReadCardSerial())
//    return;
while (! rfid.PICC_IsNewCardPresent()||! rfid.PICC_ReadCardSerial());
Serial.println("ad");
 for (int j = 0; j < 4; j++)
{
  Serial.println(rfid.uid.uidByte[j]);
 mang[sothe][j] = rfid.uid.uidByte[j];
}
//delay(1000);
}
//  //while (! rfid.PICC_IsNewCardPresent()||! rfid.PICC_ReadCardSerial());
//  Serial.println("asfdf1");
//  delay(1000);
//  //for(k;k<=sothe;
//  for (int j=0;j<4;j++)
//  {
//    mang[2][j]=rfid.uid.uidByte[j];
//    //Serial.println(mang[sothe][j]);
//  }  Serial.println("asfdf2");
//  return mang;
void setup() { 
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  for (byte i = 0; i < 6; i++) {
  key.keyByte[i] = 0xFF;
  }
 //pinMode(2, INPUT_PULLUP);
 pinMode(2, INPUT);
 //attachInterrupt(0, nhapthe, LOW); // pin 2
 pinMode(pin, LOW);
}
 
void loop() {
if(digitalRead(2)==LOW)
{
  Serial.println("asff");
  nhapthe();
}
//   Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;
//  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
//  Serial.println(rfid.PICC_GetTypeName(piccType));

//while (! rfid.PICC_IsNewCardPresent()||! rfid.PICC_ReadCardSerial());

for (int i = 0; i < 4; i++)
{
 nuidPICC[i] = rfid.uid.uidByte[i];
}
  printDec(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();
  x=isAuthorized();
  //tep =sosanh();
 Serial.println(x);
  Serial.println(sothe); 
 for (int k=0;k<=sothe;k++)
 {
 for(int i=0;i<4;i++)
 {
  Serial.print(mang[k][i]);
 }
 Serial.println();
 }
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}

