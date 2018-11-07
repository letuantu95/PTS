
void setup() {
  // put your setup code here, to run once:
pinMode(D0,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int sensorValue = analogRead(D0);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(1000);
}
