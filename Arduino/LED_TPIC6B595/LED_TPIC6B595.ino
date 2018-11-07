
//Pin to clear the register
const int clearPin = 7;// tpic sẽ mức 1.
//Pin connected to latch pin (RCK) of TPIC6B595
const int latchPin = 8;
//Pin connected to clock pin (SRCK) of TPIC6B595
const int clockPin = 12;
////Pin connected to Data in (SER IN) of TPIC6B595
const int dataPin = 11;
void setup() {
 //set pins to output because they are addressed in the main loop
 pinMode(clearPin, OUTPUT);
 pinMode(latchPin, OUTPUT);
 pinMode(dataPin, OUTPUT);  
 pinMode(clockPin, OUTPUT);
 Serial.begin(9600);
 digitalWrite( clearPin, HIGH);
 delay(100);
}
void loop() {
 for(int i=0;i<=9;i++)
 {
   so(i);so(i);so(i);so(i);so(i);so(i);
   delay(3000);
 }
 registerWrite( 0,0,0,0,0,0,0,0); registerWrite( 0,0,0,0,0,0,0,0); registerWrite( 0,0,0,0,0,0,0,0); registerWrite( 0,0,0,0,0,0,0,0);
 registerWrite( 0,0,0,0,0,0,0,0); registerWrite( 0,0,0,0,0,0,0,0);
 delay(3000);
}
void so(int i)
{
  switch (i)
  {
    case 0:
    registerWrite( 1,1,1,1,1,1,0,0);
    break;
    case 1:
    registerWrite( 0,0,0,0,1,1,0,0);//1
    break;
    case 2:
    registerWrite( 1,1,0,1,1,0,0,1);//2
    break;
    case 3:
    registerWrite( 1,0,0,1,1,1,0,1);//3
    break;
    case 4:
    registerWrite( 0,0,1,0,1,1,0,1);//4
    break;
    case 5:
    registerWrite( 1,0,1,1,0,1,0,1);//5
    break;
    case 6:
    registerWrite( 1,1,1,1,0,1,0,1);//6
    break;
    case 7:
    registerWrite( 0,0,0,1,1,1,0,0);//7
    break;
    case 8:
    registerWrite( 1,1,1,1,1,1,0,1);//8
    break;
    case 9:
    registerWrite( 1,0,1,1,1,1,0,1);//9
    break;
  }
}
void registerWrite(int a,int b,int c,int d,int e,int f,int g,int k) {
 byte bitsToSend = 0;
 // write number as bits
  bitWrite(bitsToSend, 0, k);
  bitWrite(bitsToSend, 1, a);
  bitWrite(bitsToSend, 2, b);
  bitWrite(bitsToSend, 3, c);
  bitWrite(bitsToSend, 4, d);
  bitWrite(bitsToSend, 5, e);
  bitWrite(bitsToSend, 6, f);
  bitWrite(bitsToSend, 7, g);
 // while you're shifting bits:
 digitalWrite(latchPin, LOW);
 //Serial.println(bitsToSend);
 Serial.println("_");
 
 // shift the bits out
 shiftOut(dataPin, clockPin, MSBFIRST  , bitsToSend);

 // turn on the output so the LEDs can ligh
 digitalWrite(latchPin, HIGH);
}

