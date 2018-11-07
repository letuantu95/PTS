
#define DATA 11
#define LATCH 10
#define CLOCK 12

int digits[] = {
   B00000001,
   B00000010,
   B00000100,
   B00001000,
   B00010000,
   B00100000,
   B01000000,
   B10000000,
   B00000000};

void setup() {
   pinMode(DATA, OUTPUT);
   pinMode(LATCH, OUTPUT);
   pinMode(CLOCK, OUTPUT);
   Serial.begin(9600);
}

void loop() {
   int i;
   for (i = 0; i < 9; i++) {
      Serial.println(i);
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, LSBFIRST, digits[i]);
      digitalWrite(LATCH, HIGH);
      delay(500);
   }
   delay(10000);
}
