#include <SoftwareSerial.h>
char a;
int b=-1;
int j=0;int k=0;
int c=0;
int addr = 0;
SoftwareSerial SIM900(8, 7);
String SDT="0339079404";
String RX="";
String SMS="";
unsigned long time=0;
boolean x=false;
//void save()
//{
//  int val = analogRead(0) / 4;
//  EEPROM.write(addr, val);
//  addr = addr + 1;
//  if (addr == 512)
//  addr = 0;
//  delay(5); 
//}
void call()
{
  at("AT",1000);
  SIM900.print("ATD"+SDT+";\r");
  delay(20000);
  SIM900.print("ATH\r");
  delay(1000);
}
//void sms()
//{
//  SIM900.println("AT+CMGF=1");                // Chon che do TEXT Mode
//  delay(2000);
//  SIM900.println("AT+CLIP=1");                  // Hien thi thong tin nguoi goi den
//  delay(2000);
//  SIM900.println("AT+CNMI=2,2,0,0,0");              // Hien thi truc tiep noi dung tin nhan
//  delay(1000);
//}
void Read_sms()
{
  SIM900.println("AT");//checEnd module
  delay(1000);
//  SIM900.println("AT+CMGDA=\"DEL ALL\"");//xoa all sms
  SIM900.println("AT+CMGDA=6");
  delay(1000);
  SIM900.println("AT+CMGF=1");// Chon che do TEXT Mode
  delay(1000);
  SIM900.println("AT+CSCS=\"GSM\"");
  delay(1000);
  SIM900.println("AT+CLIP=1");// Hien thi thong tin nguoi goi den
  delay(1000);
   SIM900.println("AT+CNMI=2,2,0,0,0");  // Hien thi truc tiep noi dung tin nhan
  delay(1000);
  
  //gui sms
  //at("AT+CMGS=\"" + SDT+"\"",2000);
  //at("Hshop test sim",1000);
  //SIM900.write(26);     // ctlrZ 
}
void setup()
{
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
  SIM900.begin(9600);
  delay(15000);
  Read_sms();
//  SIM900.println("AT+CNMI=2,2,0,0,0");
//  delay(1000);
////  SIM900.println("AT+CMGDA=\"DEL ALL\"");
////  delay(2000);
//  //sms();
//  //call();
//  at("AT",1000);
//  at("AT+CMGF=1",1000);
//  at("AT+CSCS=\"GSM\"",1000);
//  //at("AT+CMGS=\"" + SDT+"\"",2000);
//  //at("Hshop test sim",1000);
  delay(10000);
  call();
 // SIM900.write(26);     // ctlrZ
 time=millis();
}

void loop() {
  //call();
  while(SIM900.available())
  {
    RX = SIM900.readString();
  }
  //Serial.println("gsd");
  for(int i=0;i<RX.length();i++)
    {
      Serial.print(RX[i]);
      if(RX[i]=='V')
      {
        Serial.println(i);
        j=i+1;
      }
     
      if(RX[i]=='X')
      {
        Serial.println(i);
        k=i;
      } 
    }
    //Serial.print(j);Serial.print(k);
    for(int b=j;b<k;b++)
    {
      SMS+=RX[b];
      Serial.print(RX[b]);
     c=1;
    }
    SDT="";
    SDT=SMS;
    SMS="";
    RX="";
   if(((millis()-time)>25000)&&c==1)
   {
    Serial.println("goi");
    Serial.println(SDT);
    call(); 
    c=0;
    j=k=0;
    time=millis();
   }
  // put your main code here, to run repeatedly:
//delay(20000);
}
void at(String _atcm,unsigned long _dl){
  SIM900.print(_atcm+"\r\n");
  delay(_dl);
}
