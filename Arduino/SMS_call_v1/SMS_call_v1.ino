#include <SoftwareSerial.h>
#include <EEPROM.h>
SoftwareSerial SIM900(8, 7);
int addr_S=0;//address eeprom save
int addr_R=0;//address eeprom read
int b=-1;int x=0; int call_Warning=0;
int Start=0;int End=0;
int c=0; char a;
String SDT="0339079404";//sdt goi
String RX="";//string receive modusim
String SMS="";//string receive sdt
unsigned long time=0;
void call()
{
  c=R_Rom(120);
  Serial.println(c);
  for(int i=1;i<=c;i++)
  {
    Serial.println(i);
    SDT="";
    SDT=R_SDT(i);
    for(int i=0;i<10;i++)
    {
      Serial.print(SDT[i]);
    }
    SIM900.println("ATD"+SDT+";");
    delay(20000);
    SIM900.println("ATH");
    delay(10000);
    Check_Call();
    if(call_Warning==1)
    {
      break;
    }
  }
}
void Check_Call()
{
  while(SIM900.available())
    {
    RX = SIM900.readString();
    }
    b=RX.indexOf("129");
    Serial.println(b); 
    if(b>=0)
    { Serial.println("asda1213");
      call_Warning=1;
      RX="";
    }
    else digitalWrite(11,LOW);
    
}

void SDT_sms()//receive sdt from sms
{
  for(int i=0;i<RX.length();i++)
  {
    Serial.print(RX[i]);
    if(RX[i]=='V')
      {
        Serial.println(i);
        Start=i+1;
      }
    if(RX[i]=='X')
      {
        Serial.println(i);
        End=i;
      } 
      delay(5);
  }
  if(Start>0)
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
    Serial.println("gtri c");
    S_SDT(c,SMS);
    Serial.println(R_Rom(120));
    Send_Sms();
    Start=End=0;
    x=1;
    SIM900.println("AT+CMGDA=6");
    delay(2000);
  }
  RX="";SMS="";
}

void S_Rom(int addr_S,byte val)//save in eeprom
{
  EEPROM.write(addr_S, val);
  delay(50); 
}
void S_SDT_Rom(int addr_Stast, int addr_Stop, String SMS)//save sdt rom 
{
  Serial.println("chieu dai sms");
  Serial.println(addr_Stast);Serial.println(addr_Stop);
  int j=0;
  Serial.println("sdt dc luu");
  for(int i=addr_Stast;i<addr_Stop;i++)
  {
    S_Rom(i,(byte(SMS[j])-48));
    Serial.print(SMS[j]);
    Serial.println(R_Rom(i));
    j=j+1;
    delay(50);
  }
}
void S_SDT(int c, String SMS)//save sdt
{
  switch(c)
  {
    case 1:
      S_SDT_Rom(0,10,SMS);
      break;
    case 2:
      S_SDT_Rom(10,20,SMS);
      break;
    case 3:
      S_SDT_Rom(20,30,SMS);
      break;
    case 4:
      S_SDT_Rom(40,50,SMS);
      break;
    case 5:
      S_SDT_Rom(50,60,SMS);
      break;
    case 6:
      S_SDT_Rom(60,70,SMS);
      break;
    case 7:
      S_SDT_Rom(70,80,SMS);
      break;
    case 8:
      S_SDT_Rom(80,90,SMS);
      break;
    case 9:
      S_SDT_Rom(90,100,SMS);
      break;
  }
}

int R_Rom(int addr) //only save sdt nen use int
{ int value=0;
  value=EEPROM.read(addr);
  delay(50);
  return value;
}
String R_SDT_Rom(int addr_Stast, int addr_Stop)
{
  String number_P="";
//  Serial.println("chieu dai sms");
//  Serial.println(addr_Stast);Serial.println(addr_Stop);
  for(int i=addr_Stast;i<addr_Stop;i++)
  {
    number_P+=R_Rom(i);
  }
  return number_P;
}
String R_SDT(int c)//read sdt
{
  String number_P="";
  switch(c)
  {
    case 1:
      number_P = R_SDT_Rom(0,10);
      break;
    case 2:
      number_P = R_SDT_Rom(10,20);
      break;
    case 3:
      number_P = R_SDT_Rom(20,30);
      break;
    case 4:
      number_P = R_SDT_Rom(40,50);
      break;
    case 5:
      number_P = R_SDT_Rom(50,60);
      break;
    case 6:
      number_P = R_SDT_Rom(60,70);
      break;
    case 7:
      number_P = R_SDT_Rom(70,80);
      break;
    case 8:
      number_P = R_SDT_Rom(80,90);
      break;
    case 9:
      number_P = R_SDT_Rom(90,100);
      break;
  }
  return number_P;
}

void Read_sms()
{
  SIM900.println("AT");//checEnd module
  delay(1000);
//  SIM900.println("AT+CMGDA=\"DEL ALL\"");//xoa all sms
  SIM900.println("AT+CMGDA=6");
  delay(1000);
  SIM900.println("AT+CMGF=1");// Chon che do TEXT Mode
  delay(1000);
  while(SIM900.available())
  {
  Serial.write(SIM900.read());
  }
  SIM900.println("AT+CSCS=\"GSM\"");
  delay(1000);
//  SIM900.println("AT+CLIP=1");// Hien thi thong tin nguoi goi den
//  delay(1000);
   SIM900.println("AT+CNMI=2,2,0,0,0");  // Hien thi truc tiep noi dung tin nhan
  delay(1000);
  
  //gui sms
  //at("AT+CMGS=\"" + SDT+"\"",2000);
  //at("Hshop test sim",1000);
  //SIM900.write(26);     // ctlrZ 
}
void Send_Sms()
{
  at("AT+CMGS=\"" + SDT+"\"",2000);
  at("da nhan dc sdt dk",1000);
  SIM900.write(26);     // ctlrZ 
}

void setup()
{
  Serial.begin(9600);
  SIM900.begin(9600);
  S_Rom(120,1);//so luong sdt
  delay(15000);
  Read_sms();
  delay(10000);
  SIM900.print("ATD"+SDT+";\r");
  delay(20000);
  SIM900.print("ATH\r");
  delay(1000);
  //call();
 time=millis();
}

void loop() {
//  while(SIM900.available())
//  {
//    RX = SIM900.readString();
//  }
 //Read_sms();
 while(SIM900.available())
  {
    a=SIM900.read();
    RX+=a;
   // RX = SIM900.readString();
  }
  
  SDT_sms();
   if((millis()-time)>25000&&call_Warning==0)
   {
    Serial.println("goi");
    call(); 
    time=millis();
    Read_sms();
    x=0;
   }
}

