
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>
#define BLYNK_MAX_READBYTES  1024
char host[] = "tapit.vn";
char auth[] = "eac41632ae5c4a8eba8bdc2cfb1def5c";        //Token cua blynk
//char ssid[] = "iPhone";        //Ten wifi
char ssid[] = "NT98_A3";
char pass[] = "568568568";         //Pass wifi

#define DHTPIN D6          // Pin ket noi voi DHT
#define DHTTYPE DHT11     // Su dung cam bien DHT11
DHT dht(DHTPIN, DHTTYPE); // Cau hinh chan DHT 

SimpleTimer timer;        // Su dung timer

//Ham gui du lieu
int h,t,x,y,z,k,g;
BLYNK_WRITE(V10)
  {
    String i = param.asStr();
    delay(200);
    if (i == "0")
    {
      digitalWrite(D2,0);
      digitalWrite(D3,0);
      digitalWrite(D4,0);
      digitalWrite(D5,0);
      Blynk.virtualWrite(V10,"2");
      delay(200);
    }
    if (i == "1")
    {
      digitalWrite(D2,1);
      digitalWrite(D3,1);
      digitalWrite(D4,1);
      digitalWrite(D5,1);
      Blynk.virtualWrite(V10,"2");
      delay(200);    
   }
  }
 BLYNK_WRITE(V11)
  {
   
    String i = param.asStr();
    delay(200);
    if (i == "0")
    {
    String stt[2] = {"on", "off"};      
    String a ="{ The temperature is "+String(t)+"°C. \The humidity is\ "+String(h)+"%. \Gas concentration\ "+String(g)+". \The light in bedroom is\ " +stt[x]+". \The light in Kitchen is\ " +stt[k]+". \The fan is\ "+stt[y]+". \The heater is\ "+ stt[z]+"}";  
    Blynk.virtualWrite(V12,a) ;
    Blynk.virtualWrite(V11,"1") ;
    Serial.println(a); 
    delay(200);
    }
  }

void sendSensor()
{

  h = dht.readHumidity();     //Doc gia tri do am
  t = dht.readTemperature();  //Doc gia tri nhiet do
  // Gan du lieu vao bien virtual de hien thi len blynk
  g = analogRead(A0);// gas
  g = g*100/1023;
  delay(10);
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V1, t);
 
  // Luu y nen ban khong du energy thi co the bo qua v2 va v3
}
void setup() 
{
  pinMode(D0,OUTPUT);//loa
  Serial.begin(9600);                   // Mo Serial
  Blynk.begin(auth, ssid, pass,host);        // Ket noi voi blynk
  dht.begin();                          // Khoi tao DHT
  timer.setInterval(1000L, sendSensor); //1s doc cam bien 1 lan
  //Blynk.virtualWrite(V11,"1") ;
}
void loop() 
{
  String stt[2] = {"on", "off"};
  String b ="temperature:"+String(t)+"°C. \humidity\: "+String(h)+"%. \Gas concentration\ "+String(g)+"%. \Lights in bedroom\: " +stt[x]+". \Lights in Kitchen\: " +stt[k]+". \Fan\: "+stt[y]+". \Heater\: "+ stt[z];  

  Blynk.run(); // Chay Blynk
  x = digitalRead(D2);//den1
  y = digitalRead(D3);//quat
  z = digitalRead(D4);//nong lanh
  k = digitalRead(D5);//den2

  Blynk.virtualWrite(V2, x);
  Blynk.virtualWrite(V3, y);
  Blynk.virtualWrite(V4, z);
  Blynk.virtualWrite(V5, k);
  Blynk.virtualWrite(V6, g);
  timer.run(); // Chay SimpleTimer
  if((digitalRead(D1)==LOW)&&(t>=33))
  {
    digitalWrite(D0,1);
    Blynk.notify("Cảnh báo: Rò rỉ khí ga và nhiệt độ quá cao");
    //Blynk.email("letuantu13dt1@gmail.com", "Cảnh báo:Có rò rỉ khí ga và nhiệt độ rất cao","Cảnh báo: Rò rỉ khí ga và nhiệt độ quá cao"+b); 
  }
  else if (digitalRead(D1)==LOW)
    {
      digitalWrite(D0,1);
      Blynk.notify("Cảnh báo: Rò rỉ khí ga"); 
      //Blynk.email("letuantu13dt1@gmail.com", "Cảnh báo: rò rỉ khí ga",b);
      delay(1000);
      digitalWrite(D0,0);
    }
    else if (t>=33)
    {
      digitalWrite(D0,1);
      Blynk.notify("Cảnh báo: Nhiệt độ quá cao");
      //Blynk.email("letuantu13dt1@gmail.com", "Cảnh báo: Nhiệt độ rất cao",b);
      delay(50);
      digitalWrite(D0,0);
    }
    else 
    {
      digitalWrite(D0,0);
    }
   
   
  /*
// Debug
  Serial.print("Do am: ");
  Serial.println(h);
  Serial.print(" %\t");
  Serial.print("Nhiet do: ");
  Serial.print(t);
  Serial.println(" *C ");
  delay(2000);                // Doi chuyen doi.
  */
  
}
