#include <SoftwareSerial.h>
#include <EEPROM.h>
SoftwareSerial SIM800(8, 7);
#define cambien 2
#define loa 3
String SDT_TU="0339079404";
int addr_S=0;//address eeprom save
int addr_R=0;//address eeprom read
int b=-1;//kiem tra chuoi 129, ket noi cuoc goi thanh cong
int call_Warning=0;//bien nhan biet cuoc goi co ket noi t/c k
int Start=0;int End=0;//bien nhan sdt dk
int c=0;char a; int x=0;//c:vi tri luu sdt, 
String SDT="";//sdt goi
String RX="";//string receive modusim
String SMS="";//string receive sdt
String DELE="";//sdt nhan sms bao dele
unsigned long time=0;
unsigned long time1,time2;
//dele
int d=-1;//kiem tra chuoi: delete all
int Dele1=0;int Dele2=0;
int Set_Time=10;
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
    SIM800.println("ATD"+SDT+";");
    delay(25000);
    SIM800.println("ATH");
    delay(100);
    Check_Call();
    if(call_Warning==1)
    {
      break;
    }
    delay(10000);
  }
}
void Check_Call()
{
  while(SIM800.available())
    {
    RX = SIM800.readString();
    }
    b=RX.indexOf("CARRIER");
    Serial.println(b); 
    if(b>=0)
    { Serial.println("gat goi");
      call_Warning=1;
      RX="";
    }
}

void Check_Sms()//receive sdt from sms
{ 
  int Time_Sms1=0;int Time_Sms2=0;
  while(SIM800.available())
   {
     RX=SIM800.readString();
   }
  //check dele
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
    //dk sdt
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
    //sdt nhan sms dele
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
    //set time
    if(RX[i]=='^')
    {
      Serial.println(i);
      Time_Sms1=i+1;
    }
    if(RX[i]=='~')
    {
      Serial.println(i);
      Time_Sms2=i;
    }
  }
  //
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
    //Serial.println("gtri c");
    S_SDT(c,SMS);
    Serial.println(R_Rom(120));
    Send_Sms_Dk();
    Start=End=0;
    SIM800.println("AT+CMGDA=6");
    delay(100);
  }

//check sms dk sdt thoai
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
  if(Time_Sms1>0&&Time_Sms2>0)
  {
    for(int b=Time_Sms1;b<Time_Sms2;b++)
    {
      Serial.print(RX[b]);
      DELE+=RX[b];
      delay(5);
    }
    S_SDT_Rom(135,139,DELE);
    Time_Sms1=Time_Sms2=0;
    Set_Time=(R_Rom(135)*1000+R_Rom(136)*100+R_Rom(137)*10+R_Rom(138));
    SIM800.println("AT+CMGS=\"" + SDT_TU+"\"");
    delay(100);
    SIM800.print(Set_Time);
    delay(100);
    SIM800.write(26);     // ctlrZ 
    delay(100);
    SIM800.println("AT+CMGDA=6");
    delay(100);
  }
   //
  RX="";SMS="";DELE="";
}

void Send_Sms_Dk()
{
  c=R_Rom(120);
  SDT="";
  SDT=R_SDT(c);
  SIM800.println("AT+CMGS=\"" + SDT+"\"");
  delay(100);
  SIM800.print("ban da dang ki so dien thoai:"+SDT+" thanh cong");
  delay(100);
  SIM800.write(26);     // ctlrZ 
  delay(1000);
  SIM800.println("AT+CMGDA=6");
  delay(100);
}
void Send_Sms_Dele()
{
  SDT="";
  SDT=R_SDT_Rom(122,132);
  SIM800.println("AT+CMGS=\"" + SDT+"\"");
  delay(100);
  SIM800.print("cac so dien thoai dang ki da bi xoa");
  delay(100);
  SIM800.write(26);     // ctlrZ 
  delay(1000);
  SIM800.println("AT+CMGDA=6");
  delay(100);
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

void Read_Sms()
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

void setup()
{
  Serial.begin(9600);
  SIM800.begin(9600);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  digitalWrite(5,HIGH);
  pinMode(cambien, INPUT);
  pinMode(loa,OUTPUT);
  digitalWrite(loa,LOW);
  //S_Rom(120,0);//so luong sdt
  delay(10000);
  SIM800.println("AT");
  delay(100);
  SIM800.println("AT+CMGDA=6");
  delay(100);
//  SIM800.print("ATD"+SDT_TU+";\r");
//  delay(20000);
//  SIM800.print("ATH\r");
  while(SIM800.available())
  {
    Serial.write(SIM800.read());
  }
  delay(300);
  Read_Sms();
  delay(1000);
  Set_Time=(R_Rom(135)*1000+R_Rom(136)*100+R_Rom(137)*10+R_Rom(138));
  //call();
  time=millis();
  time1=millis();
  time2=millis();
}

void loop() {
  if(digitalRead(cambien)==1)
  {
    if(x==1)
    {
      call_Warning=0;
    }
    
    digitalWrite(4,LOW);
    Check_Sms();
    time2=millis();
    digitalWrite(loa,LOW);
    if((millis()-time1)>(Set_Time*1000))
    {
      digitalWrite(loa,HIGH);
      Check_Sms();
      if((millis()-time)>30000&&call_Warning==0)
      {
        Serial.println("goi");
        call(); 
        Read_Sms();
        //Check_Sms();
        time=millis();
      }
    }
    x=0;
  }
  if(digitalRead(cambien)==0)
  {
    if(x==0)
    {
      call_Warning=0;
    }
    digitalWrite(4,HIGH);
    Check_Sms();
    time1=millis();
    digitalWrite(loa,LOW);
    if((millis()-time2)>(Set_Time*1000))
    {
      digitalWrite(loa,HIGH);
      Check_Sms();
      if((millis()-time)>30000&&call_Warning==0)
      {
        Serial.println("goi");
        call(); 
        Read_Sms();
        //Check_Sms();
        time=millis();
      }
    }
    x=1;
  }
}

