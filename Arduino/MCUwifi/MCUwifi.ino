#include <ESP8266WiFi.h>
char ssid[] = "PSS";
char password[] = "pss201806";
void setup() {
  Serial.begin(9600);
  Serial.println("adasada");
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

void loop() {
  // put your main code here, to run repeatedly:

}
