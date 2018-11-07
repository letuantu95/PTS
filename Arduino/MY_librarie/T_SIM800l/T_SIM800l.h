#ifndef T_SIM800L_h
#define T_SIM800L_h
#include "Arduino.h"
#include <SoftwareSerial.h>

#define RX_PIN 8
#define TX_PIN 7  


class SIM800L
{
  public:
    void Print(String a);
    void Begin(); 
    String Read_Serial();
    void Print();
    void Call(String SDT);
    void Send_Sms(String SDT, String SMS);
    void S_Rom(int addr_S,byte val);
    void S_String_Rom(int addr_Stast, String SMS);
    int R_Rom(int addr);
    String R_SDT_Rom(int addr_Stast, int addr_Stop);
    void Read_Sms();
  private: 
};

#endif
