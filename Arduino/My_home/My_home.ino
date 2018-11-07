#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_MAX_READBYTES  1024
//char x[2]={"LOW","HIGH"};
int a,b;
String stt[2] = {"on", "off"};
char auth[] = "4d1b585ee27e4db1a8c216a452c728d9";
//char ssid[] = "PSS";
//char pass[] = "vuongnt201806";
char ssid[] = "NT98_A3";
char pass[] = "568568568";
//#define asInt param.asInt()
BlynkTimer timer; // Announcing the timer
unsigned long start;
BLYNK_WRITE(V2)
{
    if(param.asInt()==1)
  {
    digitalWrite(D2,HIGH);
    Blynk.virtualWrite(V2,HIGH); 
    Serial.println(param.asInt());
  }
  else
  {
    digitalWrite(D2,LOW);
    Blynk.virtualWrite(V2,LOW);
    Serial.println(param.asInt()); 
  }
}
BLYNK_WRITE(V1)
{
  if(param.asInt()==1)
  {
    digitalWrite(D1,HIGH);
    Blynk.virtualWrite(V1,HIGH);
    Serial.println(param.asInt());
  }
  else
  {
    digitalWrite(D1,LOW);
    Blynk.virtualWrite(V1,LOW); 
    Serial.println(param.asInt());
  }
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  start=millis();
}
void loop()
{
  if((millis()-start)>3600000)
  {
    a=digitalRead(D1);b=digitalRead(D2);
    Blynk.begin(auth, ssid, pass);
    digitalWrite(D1,a);digitalWrite(D2,b);
    start=millis();
  }
  Blynk.run();
  if( WiFi.status() != WL_CONNECTED)
  {
//    ketnoiwifi();
    Blynk.begin(auth, ssid, pass);
    delay(10000);
  }
}

