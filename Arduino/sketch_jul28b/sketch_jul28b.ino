 int pin = 13;
volatile int state = LOW;
void setup()
{
  pinMode(pin, OUTPUT);
  attachInterrupt(0, blink, FALLING); // pin 2
}
void loop()
{
  digitalWrite(pin, state);
}
void blink()
{
  state = !state;
}
