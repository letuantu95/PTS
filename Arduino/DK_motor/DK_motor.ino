#define KHOA  D0
#define DK1   D1
#define DK2   D2
#define RA    D3
#define V_CAN D4
#define D_HET D5
#define M_HET D6
#define DATA  D7
#define OFF_VCAN=D8
void setup() 
{
  Serial.begin(9600);
  pinMode(RA,INPUT);//co nguoi muon ra
  pinMode(V_CAN,INPUT);//hong ngoai
  pinMode(D_HET,INPUT);//cua dong het
  pinMode(M_HET,INPUT);//cua mo het
  pinMode(DATA,INPUT);//T/H
  pinMode(10,INPUT);//cua da dong het
  ////pinMode(2, INPUT_PULLUP);
  //attachInterrupt(0, ngat, HIGH);
  pinMode(DK1,OUTPUT);//DK motor
  pinMode(DK2,OUTPUT);//DK motor
  pinMode(KHOA,OUTPUT);//DK chot
}

void loop() 
{
  int data=digitalRead(DATA);
  Serial.println(data);
  int v_can=digitalRead(V_CAN);
  int d_het=digitalRead(D_HET);
  int m_het=digitalRead(M_HET);
  int donghet=digitalRead(10);
  //co t/h mo cua 
  while(digitalRead(RA)==1)
  {
    ngat();
  }
  if(data==1)
  {
    if(m_het!=1)//cua mo chua het
    {
      digitalWrite(KHOA,LOW);
      delay(1000);
      Serial.println("mo cua1");
      mocua();
    }
    else
    {
      Serial.println("cua mo het: dung cua1");
      dungcua();
    }
  }
  else//co t/h dong cua, 
  {
    if(d_het!=1&&v_can!=1)//chua dong het va k co nguoi.
    {
      Serial.println("dong cua1");
      dongcua();
    }
    else//da dong hoac co nguoi
    {
      if(d_het==1)//da dong
        {
          Serial.println("cua da dong: dung cua2");
          dungcua();
          delay(1000);
          digitalWrite(KHOA,HIGH);//chot cua lai k cho mo
        }
      else//chua dong
      {
        if(v_can==1&&m_het!=1&&d_het!=1)//co nguoi va cua chu mo het
        {
          Serial.println("mo cua 2");
          mocua();
        }
        else
        {
          if(m_het==1)
          {
            Serial.println("dung cua 3");
            dungcua();
            delay(10000);
          }
        }
      }
    }
  }
 delay(5000);
}

void ngat()
{
  Serial.print("gia tri");
  Serial.println(digitalRead(2));
  Serial.println("co nguoi");
  if(digitalRead(M_HET)==1)
  {
    Serial.println("dung cua 5");
    dungcua();
    delay(10000);
  }
  else
  {
    Serial.println("mo cua tu dong");
    mocua();
  }
  delay(2000);//bo
}
void mocua()
{
  digitalWrite(KHOA,LOW);delay(1000);
  digitalWrite(DK1,HIGH);digitalWrite(DK2,LOW);
}
void dongcua()
{
  digitalWrite(DK1,LOW);digitalWrite(DK2,HIGH);
}
void dungcua()
{
  digitalWrite(DK1,LOW);digitalWrite(DK2,LOW);
}

