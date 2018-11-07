#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 5 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 
int nuidPICC[4];
int sothe=0;//tuong ung vs 1 the
int mang[100][4];
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
while (! rfid.PICC_IsNewCardPresent()||! rfid.PICC_ReadCardSerial());
 for (int j = 0; j < 4; j++)
{
 mang[sothe][j] = rfid.uid.uidByte[j];
}
sothe++;
}
void setup() { 
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  for (byte i = 0; i < 6; i++) {
  key.keyByte[i] = 0xFF;
  }
 pinMode(2, INPUT);
} 
void loop() {
if(digitalRead(2)==LOW)
{
  Serial.println("asff");
  nhapthe();
}
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;
for (int i = 0; i < 4; i++)
{
 nuidPICC[i] = rfid.uid.uidByte[i];
}
  printDec(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();
  x=isAuthorized();
 Serial.println(x);//tra ve dung sai cua the
  Serial.println(sothe); //so phan tu cua mang
 for (int i=0;i<sothe;i++)//in cac ptu cua mang
 {
 for(int j=0;j<4;j++)
 {
  Serial.print(mang[i][j]);
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

