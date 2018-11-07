#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


#define BLYNK_MAX_READBYTES  1024
char host[] = "tapit.vn";
char auth[] = "eac41632ae5c4a8eba8bdc2cfb1def5c";        //Token cua blynk
//char ssid[] = "iPhone";        //Ten wifi
char ssid[] = "NT98_A3";
char pass[] = "568568568";         //Pass wifi
BLYNK_WRITE(V2)
 {
    String i = param.asStr();
    delay(200);
    if (i == "0")
    {
      digitalWrite(D2,0);
      Blynk.virtualWrite(V2,digitalRead(D2));
    }
    else 
    {
      digitalWrite(D2,1);
      Blynk.virtualWrite(V2,digitalRead(D2));
    }
 }
void setup() 
{
  Serial.begin(9600);                   // Mo Serial
  Blynk.begin(auth, ssid, pass,host);        // Ket noi voi blynk
                          // Khoi tao DHT
}

void loop()
{
  Blynk.run(); // Chay Blynk
}
