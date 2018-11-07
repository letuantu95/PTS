 /*
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN D4
#define RST_PIN D2
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 
byte nuidPICC[4];
byte mang[3][4]={
  {65, 246, 147, 46},
  {181, 203, 129, 99},
  {54, 44, 200, 115}
  };
bool x=true;
int y=0;
int a=0;
int b=2;
unsigned long start;
void setup() 
{ 
  Serial.begin(9600);
  //attachInterrupt(D8, apOn, HIGH);
  SPI.begin(); // Init SPI bus
  pinMode(D8,INPUT);
  pinMode(D8,INPUT);//ct hanh trinh
  pinMode(D3,OUTPUT);//khoa
  pinMode(D1,OUTPUT);//loa
  digitalWrite(D3,LOW);
  digitalWrite(D1,LOW);

 
  //pinMode(D8, INPUT_PULLUP); //Kéo điện trở lên cho chân số 2
  
  rfid.PCD_Init(); // Init MFRC522 
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
 start = millis();
}
void loop() {
//  if(b==1)
//  {
//    apOn();
//  }

//  if((millis() - start) > 60000)
//  {
//    if(digitalRead(D3)==1)
//    {
//      digitalWrite(D1,HIGH);
//    }
//    else digitalWrite(D1,LOW);
//  }
//    if((millis() - start) > 30000){
//    //Serial.println(b);
//     if(b==0){
//      //Serial.println(b);
//     digitalWrite(D3,LOW);//Serial.println("dong cua");
//     }
//  }
//Serial.println(b);
//Serial.println("adsaj");
//delay(1000);
while(digitalRead(D0)==1)
{
  
}
a=analogRead(A0);
if(a>500)
{
  b=1;
}
else b=0;
//Serial.println(a);
//Serial.println(b);
if((millis()- start)>10000)
{
  if(b==0)
  {
    digitalWrite(D3,LOW);
    y=1;
  }
}
if((b==1)&&(digitalRead(D3)==0))
  {
    digitalWrite(D1,HIGH);
  }
if((millis() - start)>50000)
{
  if(b==1)
  {
    digitalWrite(D1,HIGH);
//    delay(1000);
//    digitalWrite(D1,LOW);
  }
  else digitalWrite(D1,LOW);  
}
  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;
    digitalWrite(D1,HIGH);
    delay(100);
    digitalWrite(D1,LOW);
    start = millis();
    if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
      for (byte i = 0; i < 4; i++) {
        nuidPICC[i] = rfid.uid.uidByte[i];
      }
      x=isAuthorized();
      //Serial.println(x);
      if(x==true)
      {
        digitalWrite(D3,HIGH);
      }
      else digitalWrite(D3,LOW);
    }
    else 
    {
      y=y+1;
//      Serial.print("giatri: ");
//      Serial.println(y);
      if(y==2)
      {
        //Serial.println("mo cua");
         for (byte i = 0; i < 4; i++) {
         nuidPICC[i] = rfid.uid.uidByte[i];
        }
        x=isAuthorized();
        //Serial.println(x);
        //Serial.println("kiem tra");
        if(x==true)
        {
          digitalWrite(D3,HIGH);
          //Serial.println("cua dc mo");
        }
        else digitalWrite(D3,LOW);
        y=0;
      }
      
      if(y==1)
      {
      //Serial.println("dong cua cho kin");
      while(b==1)
      {
//        Serial.println(D8);
//        Serial.println("cua chu kin");
        digitalWrite(D1,HIGH);
        delay(1000);
        digitalWrite(D1,LOW);
        delay(1000);
      }
      //Serial.println(b);
      digitalWrite(D1,LOW);
      digitalWrite(D3,LOW);
    }
    }
  // Halt PICC
  rfid.PICC_HaltA();
  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}
//void printDec(byte *buffer, byte bufferSize) {
//  for (byte i = 0; i < bufferSize; i++) {
//    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
//    Serial.print(buffer[i], DEC);
//  }
//}

bool isSame(byte *key, byte *serial)
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
    for(byte k = 0; k<3; k++)//vòng lập tương ứng với số thẻ.
    {
      if(isSame(nuidPICC, mang[k]))
        return true;
    }
   return false;
}
//void apOn()
//  {
//    
//    Serial.println("Button is pressed");
//    delay(1000);
//    Serial.println("sadf");
//    delay(1000);
//    digitalWrite(D3,HIGH);
//    start = millis();
//  }
