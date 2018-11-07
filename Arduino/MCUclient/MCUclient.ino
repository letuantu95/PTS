#include <SPI.h>
#include <ESP8266WiFi.h>

char ssid[] = "PSS";          //  your network SSID (name) 
char password[] = "pss201806";   // your network password
//int status = WL_IDLE_STATUS;
//IPAddress server(74,125,115,105);  // Googleđịa .chỉ IP mà máy khách sẽ kết nối tới

// Initialize the client library
WiFiClient client;

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
    // if you get a connection, report back via serial:
    if (client.connect("carebook.vn", 80)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("GET /carebookcenter/api/mobile/v1/categories/5b55513977c82c8d26ab56e1 HTTP/1.0");
      client.println();     
    }
}
void loop() {
  
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
