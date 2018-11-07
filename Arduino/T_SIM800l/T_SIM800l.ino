#include "T_SIM800l.h"
#include <SoftwareSerial.h>
#define cambien 2
#define loa 3
SIM800L SIM800L1;String RX="";
String SDT="0339079404";
String DELE="";String SMS="";//string receive sdt

void Check_Sms()
{
  RX=SIM800L1.Read_Serial();
  d=RX.indexOf("delete all");
  if (d>=0)
  {
    Send_Sms_Dele();
    S_Rom(120,0);
    d=-1;
  }
  //
  for(int i=0;i<RX.length();i++)
  {
    Serial.print(RX[i]);
    if(RX[i]=='*')
      {
        Serial.println(i);
        Start=i+1;
      }
    if(RX[i]=='%')
      {
        Serial.println(i);
        End=i;
      } 
    //
    if(RX[i]=='<')
    {
      Serial.println(i);
      Dele1=i+1;
    }
    if(RX[i]=='>')
    {
      Serial.println(i);
      Dele2=i;
    }
  }
  if(Start>0&&End>0)
  {
    c=R_Rom(120);
    c=c+1;
    S_Rom(120,c);
    for(int b=Start;b<End;b++)
    {
      Serial.print(RX[b]);
      SMS+=RX[b];
      delay(5);
    }
    S_SDT(c,SMS);
    Send_Sms_Dk();
    Start=End=0;
    SIM800.println("AT+CMGDA=6");
    delay(100);
  }
   if(Dele1>0&&Dele2>0)
   {
   for(int b=Dele1;b<Dele2;b++)
    {
      Serial.print(RX[b]);
      DELE+=RX[b];
      delay(5);
    }
      S_SDT_Rom(122,132,DELE);
      Dele1=Dele2=0;
      SIM800.println("AT+CMGDA=6");
      delay(100);
   }
  RX="";SMS="";DELE="";
}
void Send_Sms_Dk()
{
  c=R_Rom(120);
  SDT="";
  SDT=R_SDT(c);
  Send_Sms(SDT,"ban da dk sdt thanh cong");
}

void setup()
{
  Serial.begin(9600);
  SIM800L1.Begin();
  pinMode(4,OUTPUT);//den
  pinMode(cambien, INPUT);
  pinMode(loa,OUTPUT);
  digitalWrite(loa,LOW);
  SIM800L1.call(SDT);
  SIM800L1.Print();
  SIM800L1.Read_Sms();
}

void loop()
{
  RX=SIM800L1.Read_Serial();
//  for(int i=0;i<RX.length();i++)
//  {
//    Serial.print(RX[i]);
//  }
  SIM800L1.Print();
}

