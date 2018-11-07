#include <DHT.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
char ssid[] = "PSS";          //  your network SSID (name) 
char password[] = "pss201806";   // your network password
int status = WL_IDLE_STATUS;
WiFiClient client;

#define DHTPIN D2 // SENSOR PIN
#define DHTTYPE DHT11 // SENSOR TYPE - THE ADAFRUIT LIBRARY OFFERS SUPPORT FOR MORE MODELS
DHT dht(DHTPIN, DHTTYPE);

long previousMillis = 0;
unsigned long currentMillis = 0;
long interval = 250000; // READING INTERVAL

char t = 0;  // TEMPERATURE VAR
char h = 0;  // HUMIDITY VAR
String data;

void setup() { 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (1)
  {
    Serial.println(".");
    delay(100);
    if (WiFi.status() == WL_CONNECTED)
      break;
  }
  Serial.println("Da vao duoc internet");

  dht.begin(); 
  delay(10000); // GIVE THE SENSOR SOME TIME TO START

  h = (int) dht.readHumidity(); 
  t = (int) dht.readTemperature(); 

  data = "";
}

void loop(){

//  currentMillis = millis();
//  if(currentMillis - previousMillis > interval) { // READ ONLY ONCE PER INTERVAL
//    previousMillis = currentMillis;
//    h = (int) dht.readHumidity();
//    t = (int) dht.readTemperature();
//  }

  data = ""temp1=" + t + "&hum1=" + h";
xczcz
  if (client.connect("localhost",80)) { // REPLACE WITH YOUR SERVER ADDRESS
    client.println("POST /test_conn/mcu_websever/add.php HTTP/1.1"); 
    client.println("Host: "POST /test_conn/mcu_websever/add.php HTTP/1.1""); // SERVER ADDRESS HERE TOO
    client.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: "); 
    client.println(data.length()); 
    client.println(); 
    client.print(data); 
  } 

  if (client.connected()) { 
    client.stop();  // DISCONNECT FROM THE SERVER
  }

  delay(300000); // WAIT FIVE MINUTES BEFORE SENDING AGAIN
}
