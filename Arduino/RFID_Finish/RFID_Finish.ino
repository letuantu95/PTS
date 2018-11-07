/*SDA=D4,SCK=D5,MOSI=D7,MISO=D6,RST=D2,6524614746,18120312999,37151166117
 * ,5444200115
*/
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define SS_PIN D4
#define RST_PIN D2
char readerID[]="cuachinh";//ten dau doc
byte UID[4];//id cua the
int a=0;
int b=2;
char ssid[] = "PSS";          //  your network SSID (name) 
char password[] = "vuongnt201806";   // your network password
unsigned long start;
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

void setup() { 
  Serial.begin(9600);
  ketnoiwifi();
  SPI.begin(); // Init SPI bus
  pinMode(A0,INPUT);//ct hanh trinh
  pinMode(D3,OUTPUT);//khoa
  pinMode(D1,OUTPUT);//loa
  digitalWrite(D3,LOW);
  digitalWrite(D1,LOW);
  rfid.PCD_Init(); // Init MFRC522 
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  start = millis();
}

void loop() 
{
//  if( WiFi.status() != WL_CONNECTED)//tu ket noi lai khi mat wifi
//  {
//    ketnoiwifi();
//    delay(1000);
//  }
  while(digitalRead(D0)==1)
  {Serial.println("sds");
  delay(10000);}
  a=analogRead(A0);
  if(a>500)
  {
    b=1;
  }
  else b=0;
  if((millis()- start)>10000)
  {
    if(b==0)
    {
      digitalWrite(D3,LOW);
    }
  }
  if((b==1)&&(digitalRead(D3)==0))
    {  
      while(true)
      {digitalWrite(D1,HIGH);
      delay(10000);
       }
    }
  if((millis() - start)>15000)
  {
  if(b==1)
  {
    digitalWrite(D1,HIGH);
  }
  else digitalWrite(D1,LOW);  
  }
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;
  digitalWrite(D1,HIGH);
  delay(100);
  digitalWrite(D1,LOW);
  delay(1000);
  start = millis();
  for (byte i = 0; i < 4; i++) 
  {
    UID[i] = rfid.uid.uidByte[i];
  }
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  sendUID();
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
          digitalWrite(D3,HIGH);
          Serial.println("mo");
        }
        else {
          digitalWrite(D3,LOW);
          Serial.println("dong");
              }
      } 
      else 
      {
        digitalWrite(D3,LOW);
      }  
      http.end(); 
}


