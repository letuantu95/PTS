 
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WidgetRTC.h>
#include <DHT.h>
#include <Servo.h>
//-----------------define Pin-----------//
#define Dspeaker D0
#define DledBedRoom D2
#define DledKitchen D5
#define Dheater D4
#define Dfan D3
#define Ddoor D7
#define VallDevice V10
#define VcheckAll V11
#define VsendStt V12
#define VledBedRoom V2
#define VledKitchen V5
#define Vheater V4
#define Vfan V3
#define Vdoor V7
#define VselectDeviceTimer V15
#define VreadGoogleTimerStart V24
#define VreadGoogleTimerStart V25
#define VreadAppTimer V23
#define VshowFanTimer V16
#define VshowHeaterTimer V17
#define Vtemp V30
#define Vhumidi V31
#define Vservo V7
#define Dservo D7


#define DHTPIN D6          // Pin ket noi voi DHT
#define DHTTYPE DHT11     // Su dung cam bien DHT11


//---------------define varible and const-------------//
BlynkTimer timer; // Announcing the timer
WidgetRTC rtc;
DHT dht(DHTPIN, DHTTYPE); // Cau hinh chan DHT 
struct timeType { 
  int hh;
  int mm;
  };
timeType currentTime{-1,-1};
timeType deviceVoiceTimeStart[2] = {{-1,-1},{-1,-1}};
timeType deviceVoiceTimeStop[2] = {{-1,-1},{-1,-1}};
timeType timeInputStart[2] = {{-1,-1},{-1,-1}};
timeType timeInputStop[2] = {{-1,-1},{-1,-1}};
int Vpin[2] = {Vfan, Vheater};
int VdisplayTimer[2] = {VshowFanTimer, VshowHeaterTimer};
int deviceIndex[2] = {0,0};
String device[2] = {"fan", "heater"};
String state[2] = {"opend", "closed"};
String stt[2] = {"on", "off"};     
uint8_t Dpin[2] = {Dfan, Dheater};
int n = 2;
int deviceSelect = 0;
char auth[] = "eac41632ae5c4a8eba8bdc2cfb1def5c";
char tokenB[] = "013087bd76e74f81b0c32caa2528e8fe"; //from Tapit.vn
//char ssid[] = "TOP";  //Tên wifi
//char pass[] = "0968457018";     //Mật khẩu wifi
char ssid[] = "NT98_A3";  //Tên wifi
char pass[] = "568568568";     //Mật khẩu wifi
char host[] = "tapit.vn";
WidgetBridge bridge1(V1);
Servo myServo;  // create servo object to control a servo 

int h,t,x,y,z,k,g, doorStt;



BLYNK_WRITE(VallDevice)
  {
    String i = param.asStr();
    if (i == "0")
    {
      digitalWrite(DledBedRoom,0);
      digitalWrite(Dfan,0);
      digitalWrite(Dheater,0);
      digitalWrite(DledKitchen,0);
      Blynk.virtualWrite(VallDevice,"2");
    }
    if (i == "1")
    {
      digitalWrite(DledBedRoom,1);
      digitalWrite(Dfan,1);
      digitalWrite(Dheater,1);
      digitalWrite(DledKitchen,1);
      Blynk.virtualWrite(VallDevice,"2");   
   }
  }
 BLYNK_WRITE(VcheckAll)
  {
    String i = param.asStr();
    if (i == "0")
    {
     
    String allStt ="{ The temperature is "+String(t)+"°C. \The humidity is\ "+String(h)+"%. \Gas concentration\ "+String(g)+". \The light in bedroom is\ " +stt[x]+". \The light in Kitchen is\ " +stt[k]+". \The fan is\ "+stt[y]+". \The heater is\ "+ stt[z]+ ". \The door is\ " + state[doorStt] + "}";  
    Blynk.virtualWrite(VsendStt,allStt) ;
    Blynk.virtualWrite(VcheckAll,"1") ;
    }
  }
BLYNK_CONNECTED() {
  // Request Blynk server to re-send latest values for all pins
  Blynk.syncVirtual(VledBedRoom);
  Blynk.syncVirtual(Vfan);
  Blynk.syncVirtual(Vheater);
  Blynk.syncVirtual(VledKitchen);
  Blynk.syncVirtual(Vdoor);
  bridge1.setAuthToken(tokenB); // Place the AuthToken of the second hardware here
}

//-----Led BedRoom-----//
BLYNK_WRITE(VledBedRoom){
 int stt = param.asInt();
 digitalWrite(DledBedRoom,stt);
}

//-----Led Kitchen -----//
BLYNK_WRITE(VledKitchen){
 int stt = param.asInt();
 digitalWrite(DledKitchen,stt);
}

//-----Fan -----//
BLYNK_WRITE(Vfan){
 int stt = param.asInt();
 digitalWrite(Dfan,stt);
}

//-----Heater -----//
BLYNK_WRITE(Vheater){
 int stt = param.asInt();
 digitalWrite(Dheater,stt);
}
//-----Door -----//


//----Read Timer from app------//
BLYNK_WRITE(VreadAppTimer) {
  TimeInputParam t(param);
  // Process start time
  int n = deviceSelect-1;
  Serial.println("n = " + String(n));
  if (t.hasStartTime() && n >= 0 ){
    timeInputStart[n].hh = t.getStartHour();
    timeInputStart[n].mm = t.getStartMinute();
  }
  if (t.hasStopTime() && deviceSelect != 0){
    timeInputStop[n].hh =  t.getStopHour();
    timeInputStop[n].mm = t.getStopMinute();
  }
  String stt = "The " + device[n] + " on at " + String( timeInputStart[n].hh) + ":" +  String( timeInputStart[n].mm) + ", off at " + String( timeInputStop[n].hh) + ":" +  String( timeInputStop[n].mm);
  Serial.println("Stt = " + stt);
  Blynk.virtualWrite(VdisplayTimer[n],stt);
  deviceSelect = 0;
  Blynk.virtualWrite(VselectDeviceTimer,"Select Device");
  
  
}

//-----Read device from app---------//
BLYNK_WRITE(VselectDeviceTimer) {
   deviceSelect = param.asInt();
}

//----Read TimeStart and device from Google------//
BLYNK_WRITE(VreadGoogleTimerStart){
  String voiceTimeStartStr = param.asStr();
  int deviceNum = voiceTimeStartStr.substring(6,7).toInt();
  timeInputStart[deviceNum].hh = voiceTimeStartStr.substring(0,2).toInt();
  timeInputStart[deviceNum].mm = voiceTimeStartStr.substring(3,5).toInt();
  String stt;
  if (timeInputStop[deviceNum].hh != -1)
    stt = "The " + device[deviceNum] + " on at " + String( timeInputStart[deviceNum].hh) + ":" +  String( timeInputStart[deviceNum].mm) + ", off at " +  String( timeInputStop[deviceNum].hh) + ":" +  String( timeInputStop[deviceNum].mm);
  else
    stt = "The " + device[deviceNum] + " on at " + String( timeInputStart[deviceNum].hh) + ":" +  String( timeInputStart[deviceNum].mm);
  Blynk.virtualWrite(VdisplayTimer[deviceNum],stt);
}

//----Read TimeStop and device from Google------//
BLYNK_WRITE(VreadGoogleTimerStop){
  String voiceTimeStopStr = param.asStr();
  int deviceNum = voiceTimeStopStr.substring(6,7).toInt();
  timeInputStop[deviceNum].hh = voiceTimeStopStr.substring(0,2).toInt();
  timeInputStop[deviceNum].mm = voiceTimeStopStr.substring(3,5).toInt();
  String stt;
  if (  timeInputStart[deviceNum].hh != -1 )
    stt = "The " + device[deviceNum] + " on at " + String( timeInputStart[deviceNum].hh) + ":" +  String( timeInputStart[deviceNum].mm) + ", off at " + String( timeInputStop[deviceNum].hh) + ":" +  String( timeInputStop[deviceNum].mm);
  else
    stt = "The " + device[deviceNum] +  " off at " + String( timeInputStop[deviceNum].hh) + ":" +  String( timeInputStop[deviceNum].mm);
  Blynk.virtualWrite(VdisplayTimer[deviceNum],stt);
}
void setup()
{
   pinMode(Dspeaker,OUTPUT);//loa
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass,host);
  dht.begin();
  rtc.begin();
  timer.setInterval(2000L, myTimerEvent);
  timer.setInterval(1000L, checkStt);
  myServo.attach(Dservo);  // attaches the servo on GIO2 to the servo object 
}

BLYNK_WRITE(Vtemp)
{
  t = param.asInt();
  Serial.println("Temp recieve from B " + String(t));
}
BLYNK_WRITE(Vhumidi)
{ 
  h = param.asInt();
  Serial.println("Humidi recieve from B " + String(h));
}

BLYNK_WRITE(Vservo){
  doorStt = param.asInt();
 if (doorStt == 0)
  {
    myServo.write(100); 
  Serial.println("Servo  " + String(100));
  }
 else if (doorStt == 1 )
  {
    myServo.write(10);
  Serial.println("Servo " + String(10));
  } 
}



void processTimer(uint8_t Dpin, int stt1, int Vpin, int stt2, timeType timeP){
  digitalWrite(Dpin, stt1);
  Blynk.virtualWrite(Vpin, stt2);
  timeP.hh = timeP.mm = -1;
}
void myTimerEvent(){
  currentTime.hh = hour();
  currentTime.mm = minute();
  for (int i = 0 ; i < n; i ++){
   if ( currentTime.hh == timeInputStart[i].hh && currentTime.mm == timeInputStart[i].mm )
      processTimer(Dpin[i], LOW, Vpin[i], LOW, timeInputStart[i]);
   if ( currentTime.hh == timeInputStop[i].hh && currentTime.mm == timeInputStop[i].mm )
   {
      processTimer(Dpin[i], HIGH, Vpin[i], HIGH, timeInputStop[i]);
      Blynk.virtualWrite(VdisplayTimer[i]," ");
   }
      
  } 
}
void checkStt() {
  x = digitalRead(DledBedRoom);//den1
  y = digitalRead(Dfan);//quat
  z = digitalRead(Dheater);//nong lanh
  k = digitalRead(DledKitchen);//den2

  String b ="temperature:"+String(t)+"°C. \humidity\: "+String(h)+"%. \Gas concentration\ "+String(g)+"%. \Lights in bedroom\: " +stt[x]+". \Lights in Kitchen\: " +stt[k]+". \Fan\: "+stt[y]+". \Heater\: "+ stt[z] + ". \The door is\ " + state[doorStt];  
  int gasStt = digitalRead(D1);
  if(( gasStt == LOW ) && ( t >=35 ))
  {
    digitalWrite(Dspeaker,1);
    Blynk.notify("Cảnh báo: Rò rỉ khí ga và nhiệt độ quá cao");
    Blynk.email("letuantu13dt1@gmail.com", "Cảnh báo:Có rò rỉ khí ga và nhiệt độ rất cao","Cảnh báo: Rò rỉ khí ga và nhiệt độ quá cao"+b); 
  }
  else if ( gasStt == LOW )
    {
      digitalWrite(Dspeaker,1);
      Blynk.notify("Cảnh báo: Rò rỉ khí ga"); 
      Blynk.email("letuantu13dt1@gmail.com", "Cảnh báo: rò rỉ khí ga",b);
      delay(1000);
      digitalWrite(Dspeaker,0);
    }
    else if ( t >=35 )
    {
      digitalWrite(Dspeaker,1);
      Blynk.notify("Cảnh báo: Nhiệt độ quá cao");
      Blynk.email("letuantu13dt1@gmail.com", "Cảnh báo: Nhiệt độ rất cao",b);
      delay(50);
      digitalWrite(Dspeaker,0);
    }
    else 
    {
      digitalWrite(Dspeaker,0);
    }
}

void loop()
{
  Blynk.run();
  timer.run();
}

