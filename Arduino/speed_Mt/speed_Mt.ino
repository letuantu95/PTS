#define cambien 2
#define loa 3
int a;
//int a=0,b=0;
unsigned long time1;
void setup() {
   Serial.begin(9600);
   pinMode(4,OUTPUT);
   pinMode(cambien, INPUT);
   pinMode(loa,OUTPUT);
   digitalWrite(3,LOW);
   time1=millis();
}
void loop() {
   while(digitalRead(cambien)==1)
   {
    digitalWrite(4,LOW);
    if((millis()-time1>15000))
    {
      Serial.println("sang1");
      digitalWrite(loa,HIGH);
    }
    delay(100);
    if(digitalRead(cambien)==0)
    {
      Serial.println("tat1");
      digitalWrite(loa,LOW);
      digitalWrite(4,HIGH);
      time1=millis();
    }
   }
   while(digitalRead(cambien)==0)
   {
    digitalWrite(4,HIGH);
    if((millis()-time1>15000))
    {
      Serial.println("sang2");
      digitalWrite(loa,HIGH);
    }
    delay(100);
    if(digitalRead(cambien)==1)
    {
      Serial.println("tat2");
      digitalWrite(loa,LOW);
      digitalWrite(4,LOW);
      time1=millis();
    }
   }
}
