#include <SoftwareSerial.h>
char inchar;
int i=0;
SoftwareSerial SIM900(8, 7);
String SDT="0528320340";
String RX="";
unsigned long time=0;
void setup()
{
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
  
  //SIM900power();
  SIM900.begin(9600);
  delay(10000); 
  //SIM900.print("AT+CLIP=1\r"); // turn on caller ID notification,bước này quan trọng.
  delay(100); 
  time=millis(); 
}



void loop()
{
  if(i==0)
  {
  SIM900.print("ATD"+SDT+";\r");
  delay(15000);
  SIM900.print("ATH\r");
  delay(1000);
  while (SIM900.available()) { //xóa hết bộ đệm
      SIM900.read();
      delay(3);
  }
  digitalWrite(11,LOW);
  i=1;
  }
  //SIM900.print("AT+CLIP=1\r");
  delay(100); 
  if(SIM900.available() >0)
  {  
   inchar=SIM900.read();
   Serial.println(inchar);
   if(inchar=='0')
   {
      digitalWrite(11,HIGH);
      delay(5000);
      SIM900.print("ATH\r");
      
      delay(10000);
      i=0;
      while (SIM900.available()) { //xóa hết bộ đệm
      SIM900.read();
      delay(3);
      
      }
    }
    
  }
  
}
