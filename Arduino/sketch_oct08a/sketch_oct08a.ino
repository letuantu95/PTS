#include <SoftwareSerial.h>
SoftwareSerial SIM900(8, 7);//Rx -10-Tx-11

void setup()
{
  Serial.begin(9600);
  SIM900.begin(9600);         
  SIM900power();  
  delay(15000);  
}
void SIM900power()
{
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(5000);// nếu module sim cần kích hoạt mức 0 thì làm ngược lại: cho chân 9 xuống thấp  trong 1 giây rồi lên cao.
}
void call()
{
SIM900.println("AT");
delay(300);
SIM900.print("ATD"); //Specify the number to call
SIM900.print("0528320340"); // đưa số điện thoại cần gọi test vào đây.
SIM900.println(";");
delay (20000);// gọi trong 20 giây.
  SIM900.println("ATH");   // kết thúc cuộc gọi.
}
void loop()
{
  call(); // test gọi
  SIM900power();   // tắt module sim
  while(SIM900.available())
  {
    Serial.write(SIM900.read());
  }
  delay(10000);
}
