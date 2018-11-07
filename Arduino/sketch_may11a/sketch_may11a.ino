#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

#include <DHT.h>
#define DHTPIN D6          // Pin ket noi voi DHT
#define DHTTYPE DHT11     // Su dung cam bien DHT11
DHT dht(DHTPIN, DHTTYPE); // Cau hinh chan DHT 
#define Vspeaker V9
#define VledYard V10
#define Vtemp V30
#define Vhumidi V31
#define VgasStt V32
#define Vgas V33

#define DledYard D0
#define Dgas D1
#define Dspeaker D3



WidgetBridge bridgeA(V10);

char auth[] = "013087bd76e74f81b0c32caa2528e8fe";  // Quan token Blynk server
// char tokenA[] = "3dddac1594e74646bde292060be39113";//from Blnyk
char tokenA[] = "eac41632ae5c4a8eba8bdc2cfb1def5c";//from Tapit.vn
char ssid[] = "NT98_A3";  //Tên wifi
char pass[] = "568568568";     //Mật khẩu wifi
//char ssid[] = "TOP";  //Tên wifi
//char pass[] = "0968457018";     //Mật khẩu wifi
char host[] = "tapit.vn";

BLYNK_CONNECTED() {
  Blynk.syncVirtual(Vspeaker);
  Blynk.syncVirtual(VledYard);
  bridgeA.setAuthToken(tokenA); // Place the AuthToken of the second hardware here
}
void readSensor ()
{
  // int h = dht.readHumidity();     //Doc gia tri do am
  // int t = dht.readTemperature();  //Doc gia tri nhiet do
  int g = digitalRead(D1);
  int j = (analogRead(A0) * 100)/1023;

  // bridgeA.virtualWrite(VgasStt,g);
  // bridgeA.virtualWrite(Vgas,j);
  Serial.println("GasStt: " + String(g) + " Gas value: " + String(j) );

//  if (t <= 100 && h <=100)
//    {
//      bridgeA.virtualWrite(Vtemp,t);
//      bridgeA.virtualWrite(Vhumidi,h);
//      Serial.println("Temp = " + String(t) + " Humidi = " + String(h));
//    }
  
}
void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, host);
  // timer.setInterval(2000L, readSensor);
pinMode(DledYard, OUTPUT);
pinMode(Dspeaker, OUTPUT);
  pinMode(Dgas, INPUT);
  pinMode(A0, INPUT);
}
BLYNK_WRITE(Vspeaker) {
  int stt = param.asInt();
  Serial.println("Speaker Stt: " + String(stt));
  digitalWrite(Dspeaker, stt);
}

BLYNK_WRITE(VledYard) {
  int stt = param.asInt();
  Serial.println("Led yard STT: " + String(stt));
  digitalWrite(DledYard,stt);
}

void loop()
{
  Blynk.run();
  // timer.run();
   int a = digitalRead(D1);
  int j = (analogRead(A0) * 100)/1023;
  Serial.println("D1 = " +String(a));
  Serial.println("A0 = " + String(j));
  delay(2000);
}
