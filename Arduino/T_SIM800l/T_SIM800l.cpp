#include <SoftwareSerial.h>
#include "T_SIM800l.h"
#include <EEPROM.h>

SoftwareSerial SIM800(RX_PIN,TX_PIN);

void SIM800L::Begin(){
  SIM800.begin(9600);
  //Serial.begin(9600);
}

void SIM800L::Print()
{
  while(SIM800.available())
  {
    Serial.write(SIM800.read());
  }
}

String SIM800L::Read_Serial()
{
  String RX="";
  while(SIM800.available())
  {
    RX=SIM800.readString();
  }
  return RX;
}

void SIM800L::Call(String SDT)
{
  SIM800.println("ATD"+SDT+";");
  delay(20000);
  SIM800.println("ATH");
  delay(100); 
}

void SIM800L::Send_Sms(String SDT, String SMS)
{
  SIM800.println("AT+CMGS=\"" + SDT+"\"");
  delay(100);
  SIM800.print(SMS);
  delay(100);
  SIM800.write(26);     // ctlrZ 
  delay(1000);
  SIM800.println("AT+CMGDA=3");// dele sms da send
  delay(100);
}

void SIM800L::S_Rom(int addr_S,byte val)
{
  EEPROM.write(addr_S, val);
  delay(5);
}

void SIM800L::S_String_Rom(int addr_Stast, String SMS)
{
  int j=0; int addr_Stop = SMS.length();
  for(int i=addr_Stast;i<addr_Stop;i++)
  {
    S_Rom(i,(byte(SMS[j])-48));
    j=j+1;
    delay(5);
  }
}  

int SIM800L::R_Rom(int addr)
{
  int value=0;
  value=EEPROM.read(addr);
  delay(50);
  return value;
}

String SIM800L::R_SDT_Rom(int addr_Stast, int addr_Stop)
{
  String string_1="";
  for(int i=addr_Stast;i<addr_Stop;i++)
  {
    string_1+=R_Rom(i);
  }
  return string_1;
}

void SIM800L::Read_Sms()
{
  SIM800.println("AT+CMGF=1");// Chon che do TEXT Mode
  delay(100);
  SIM800.println("AT+CSCS=\"GSM\"");
  delay(100);
//  SIM800.println("AT+CLIP=1");// Hien thi thong tin nguoi goi den
//  delay(1000);
  SIM800.println("AT+CNMI=2,2,0,0,0");  // Hien thi truc tiep noi dung tin nhan
  delay(100);
  while(SIM800.available())
  {
    Serial.write(SIM800.read());
  }
}


