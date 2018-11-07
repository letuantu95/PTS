void setup() {
 

}

void loop() {
  digitalWrite(D3,0);
  digitalWrite(D5,1);
  if(digitalRead(D2)==0)
  {
    digitalWrite(D4,0);
    delay(50);
  }
  else digitalWrite(D4,1);
  delay(5000);
  digitalWrite(D5,1);
}
