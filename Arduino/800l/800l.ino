/* nhan cuoc goi den tat tb*/
#include <SoftwareSerial.h>
char a;
int b=-1;
int i=0;
SoftwareSerial SIM900(8, 7);
String SDT="0339079404";
String RX="";
unsigned long time=0;
boolean x=false;
void setup()
{
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
  SIM900.begin(9600);
  delay(10000);
  //SIM900.print("ATZ");
  delay(1000); 
  time=millis();
}

void loop()
{
  SIM900.print("ATD"+SDT+";\r");
  delay(20000);
  SIM900.print("ATH\r");
  delay(1000);
  while (SIM900.available()) { //xóa hết bộ đệm
      a=(char)SIM900.read();
      Serial.print(a);
      RX+=a;
      delay(3);
  }
  b=RX.indexOf("129");
  Serial.println(b); 
  if(b>=0)
  { Serial.println("asd");
    digitalWrite(11,HIGH);
    //b=-1;
    //delay(1000);
    RX="";
  }
  else digitalWrite(11,LOW);
  delay(10000);
}
