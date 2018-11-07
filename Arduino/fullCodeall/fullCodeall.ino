#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WidgetRTC.h>
#include <Servo.h>
//-----------------define Pin-----------//
#define Dspeaker D0
#define DledLivingRoom D1
#define DledBedRoom D2
#define Dfan D3
#define Dheater D4
#define DledKitchen D5
#define DledBathRoom D6
#define Ddoor D8
#define DairConditioner D7
#define Dwindow D9
#define DledYard D10

#define VledLivingRoom V1
#define VledBedRoom V2
#define Vfan V3
#define Vheater V4
#define VledKitchen V5
#define VledBathRoom V6
#define Vdoor V8
#define VairConditioner V7
#define Vwindow V9
#define VledYard V10

#define VallDevice V19
#define VcheckAll V11
#define VsendStt V12
#define VdeviceB V14

#define VlightDisplay V20

#define VselectDeviceTimer V15
#define VshowFanTimer V16
#define VshowHeaterTimer V17
#define VshowAirConditionerTimer V18
#define VreadAppTimer V23
#define VreadGoogleTimerStart V24
#define VreadGoogleTimerStop V25
#define VlightRes V26


#define Vtemp V30
#define Vhumidi V31
#define VgasStt V32
#define Vgas V33

#define lightSensor A0
#define asInt param.asInt()
#define asStr param.asStr()


//---------------define varible and const-------------//
BlynkTimer timer; // Announcing the timer
WidgetRTC rtc;
struct timeType { 
  int hh;
  int mm;
  };
timeType currentTime{-1,-1};
timeType deviceVoiceTimeStart[3] = {{-1,-1}, {-1,-1}, {-1,-1}};
timeType deviceVoiceTimeStop[3] = {{-1,-1}, {-1,-1}, {-1,-1}};
timeType timeInputStart[3] = {{-1,-1}, {-1,-1}, {-1,-1}};
timeType timeInputStop[3] = {{-1,-1}, {-1,-1}, {-1,-1}};
int Vpin[3] = {Vfan, Vheater, VairConditioner};
int VdisplayTimer[3] = {VshowFanTimer, VshowHeaterTimer, VshowAirConditionerTimer};
String device[3] = {"fan", "heater", "air_conditioner"};
String stt[2] = {"on", "off"};
String state[2] = {"opened", "closed"};
uint8_t Dpin[3] = {Dfan, Dheater,DairConditioner};
uint8_t led[4] ={DledLivingRoom, DledBedRoom, DledKitchen, DledBathRoom };
int Vled[4]={VledLivingRoom, VledBedRoom, VledKitchen, VledBathRoom};

uint8_t Ddivice[3] = {Dfan, Dheater, DairConditioner};
int n = 3;
int deviceSelect = 0;
char auth[] = "e2166f454dfc4e7493d15cbd0ebceabf";
char tokenB[] = "83486216d8ba48ee977e621c6be720a1"; //from Tapit.vn
//char ssid[] = "TOP";  //Tên wifi
//char pass[] = "0968457018";     //Mật khẩu wifi
char ssid[] = "NT98_A3";  //Tên wifi
char pass[] = "568568568";     //Mật khẩu wifi
char host[] = "tapit.vn";
WidgetBridge bridge1(VdeviceB);
Servo myServoDoor, myServoWindow;  // create servo object to control a servo 

int x[4];
int y[3];
int z[2];
int h,t,g;
int lightThresh = 300;
String b = "";

//--------Turn all device-----------//
BLYNK_WRITE(VallDevice)
  {
    String i = asStr;
    if (i == "0")
    {
      for (int i = 0 ; i < 4; i ++) {
        digitalWrite(led[i], LOW);
        Blynk.virtualWrite(Vled[i],LOW);
      }
      for (int i = 0 ; i < 3; i ++) {
        digitalWrite(Ddivice[i], LOW);
        Blynk.virtualWrite(Vpin[i],LOW);
      }
      myServoDoor.write(100);
      Blynk.virtualWrite(Vdoor,LOW);
      myServoWindow.write(100);
      Blynk.virtualWrite(Vwindow,LOW);
      Blynk.virtualWrite(VallDevice,"2");
    }
    if (i == "1")
    {
      for (int i = 0 ; i < 4; i ++){
        digitalWrite(led[i], HIGH);
        Blynk.virtualWrite(Vled[i],HIGH);
      }
      for (int i = 0 ; i < 3; i ++){
        digitalWrite(Ddivice[i], HIGH);
        Blynk.virtualWrite(Vpin[i],HIGH);
      }
      myServoDoor.write(10);
      Blynk.virtualWrite(Vdoor,HIGH);
      myServoWindow.write(10);
      Blynk.virtualWrite(Vwindow,HIGH);
      Blynk.virtualWrite(VallDevice,"2"); 
   }
  }

  //--------Check all status----//
 BLYNK_WRITE(VcheckAll)
  {
    String i = asStr;
    if (i == "0")
    {  
      String allStt = "{" + b + "}";
      Blynk.virtualWrite(VsendStt,allStt);
      Blynk.virtualWrite(VcheckAll,"1");
    }
  }
BLYNK_CONNECTED() {
  // Request Blynk server to re-send latest values for all pins

  Blynk.syncVirtual(VledLivingRoom);
  Blynk.syncVirtual(VledBedRoom);
  Blynk.syncVirtual(VledKitchen);
  Blynk.syncVirtual(VledBathRoom);
  Blynk.syncVirtual(Vfan);
  Blynk.syncVirtual(Vheater);
  Blynk.syncVirtual(VairConditioner);
  Blynk.syncVirtual(Vdoor);
  Blynk.syncVirtual(Vwindow);

  bridge1.setAuthToken(tokenB); // Place the AuthToken of the second hardware here
}

//-----Led Living-----//
BLYNK_WRITE(VledLivingRoom){
  int stt = asInt;
  digitalWrite(DledLivingRoom,stt);
}

//-----Led BedRoom-----//
BLYNK_WRITE(VledBedRoom){
  int stt = asInt;
 digitalWrite(DledBedRoom,stt);
}

//-----Led Kitchen -----//
BLYNK_WRITE(VledKitchen){
  int stt = asInt;
  digitalWrite(DledKitchen,stt);
}

//-----Led BathRoom-----//
BLYNK_WRITE(VledBathRoom){
  int stt = asInt;
  digitalWrite(DledBathRoom,stt);
}

//-----Fan -----//
BLYNK_WRITE(Vfan){
 int stt = asInt;
 digitalWrite(Dfan,stt);
}

//-----Heater -----//
BLYNK_WRITE(Vheater){
 int stt = asInt;
 digitalWrite(Dheater,stt);

}
//-----AirConditioner -----//
BLYNK_WRITE(VairConditioner){
 int stt = asInt;
 digitalWrite(DairConditioner,stt);

}
//-----Temp -----//
BLYNK_WRITE(Vtemp)
{
  t = asInt;
  if (t >=42) {
    checkStt();
    digitalWrite(Dspeaker,1);
    Blynk.notify("Cảnh báo: Nhiệt độ quá cao");
    Blynk.email("letuantu13dt1@gmail.com", "Cảnh báo: Nhiệt độ rất cao",b);
    delay(50);
    digitalWrite(Dspeaker,0);
  }
  else 
    digitalWrite(Dspeaker, 0);
}

//--------Humidy-------//
BLYNK_WRITE(Vhumidi)
{ 
  h = asInt;
}

//---------Read gas sensor------//
BLYNK_WRITE(Vgas) {
  g = asInt;
}

//---------Door-----------//
BLYNK_WRITE(Vdoor){
  z[0] = asInt;
 if (z[0] == 0)
  {
    if (analogRead(lightSensor) < lightThresh) {
      digitalWrite(DledLivingRoom, LOW);
      Blynk.virtualWrite(VledLivingRoom,LOW);
    }
    myServoDoor.write(100); 
  }
 else if (z[0] == 1 )
  {
    myServoDoor.write(10);
  } 
}

//-----------Window--------//
BLYNK_WRITE(Vwindow){
  z[1] = asInt;
 if (z[1] == 0)
  {
    myServoWindow.write(100); 
  }
 else if (z[1] == 1 )
  {
    myServoWindow.write(10);
  } 
}

//----------Gas Alert----------------//
BLYNK_WRITE(VgasStt) {
  int stt = asInt;
  if (stt == LOW) {
    checkStt();
    digitalWrite(Dspeaker,1);
    Blynk.notify("Cảnh báo: Rò rỉ khí ga"); 
    Blynk.email("letuantu13dt1@gmail.com", "Cảnh báo: rò rỉ khí ga",b);
    delay(1000);
    digitalWrite(Dspeaker,0);
    }
  else 
    digitalWrite(Dspeaker, 0);
}


//----Read Timer from app------//
BLYNK_WRITE(VreadAppTimer) {
  TimeInputParam t(param);
  // Process start time
  int n = deviceSelect-1;
  if (t.hasStartTime() && n >= 0 ){
    timeInputStart[n].hh = t.getStartHour();
    timeInputStart[n].mm = t.getStartMinute();
  }
  if (t.hasStopTime() && deviceSelect != 0){
    timeInputStop[n].hh =  t.getStopHour();
    timeInputStop[n].mm = t.getStopMinute();
  }
  String stt = "The " + device[n] + " on at " + String( timeInputStart[n].hh) + ":" +  String( timeInputStart[n].mm) + 
    ", off at " + String( timeInputStop[n].hh) + ":" +  String( timeInputStop[n].mm);
  Blynk.virtualWrite(VdisplayTimer[n],stt);
  deviceSelect = 0;
  Blynk.virtualWrite(VselectDeviceTimer,"Select Device");
  
  
}

//-----Read device from app---------//
BLYNK_WRITE(VselectDeviceTimer) {
  deviceSelect = asInt;
  Blynk.virtualWrite(V0,deviceSelect-1);
}

//----Read TimeStart and device from Google------//
BLYNK_WRITE(VreadGoogleTimerStart){
  String voiceTimeStartStr = asStr;
  int deviceNum = voiceTimeStartStr.substring(6,7).toInt();
  timeInputStart[deviceNum].hh = voiceTimeStartStr.substring(0,2).toInt();
  timeInputStart[deviceNum].mm = voiceTimeStartStr.substring(3,5).toInt();
  String stt;
  if (timeInputStop[deviceNum].hh != -1)
    stt = "The " + device[deviceNum] + " on at " + String( timeInputStart[deviceNum].hh) + ":" +  
      String( timeInputStart[deviceNum].mm) + ", off at " +  String( timeInputStop[deviceNum].hh) + ":" +  String( timeInputStop[deviceNum].mm);
  else
    stt = "The " + device[deviceNum] + " on at " + String( timeInputStart[deviceNum].hh) + ":" +  String( timeInputStart[deviceNum].mm);

  Blynk.virtualWrite(VdisplayTimer[deviceNum],stt);
}

//----Read TimeStop and device from Google------//
BLYNK_WRITE(VreadGoogleTimerStop){
  String voiceTimeStopStr = asStr;
  int deviceNum = voiceTimeStopStr.substring(6,7).toInt();
  timeInputStop[deviceNum].hh = voiceTimeStopStr.substring(0,2).toInt();
  timeInputStop[deviceNum].mm = voiceTimeStopStr.substring(3,5).toInt();
  String stt;
  if (  timeInputStart[deviceNum].hh != -1 )
    stt = "The " + device[deviceNum] + " on at " + String( timeInputStart[deviceNum].hh) + ":" +  
      String( timeInputStart[deviceNum].mm) + ", off at " + String( timeInputStop[deviceNum].hh) + ":" +  String( timeInputStop[deviceNum].mm);
  else
    stt = "The " + device[deviceNum] +  " off at " + String( timeInputStop[deviceNum].hh) + ":" +  String( timeInputStop[deviceNum].mm);
     
  Blynk.virtualWrite(VdisplayTimer[deviceNum],stt);
}
void setup()
{
   
  // Debug console
  Blynk.begin(auth, ssid, pass,host);
  pinMode(Dspeaker,OUTPUT);//loa
  for (int i = 0 ; i < 4 ; i ++)
    pinMode(led[i], OUTPUT);
  for (int i = 0 ; i < 3 ; i ++)
    pinMode(Ddivice[i],OUTPUT);
  pinMode(DledYard, OUTPUT);
  myServoDoor.attach(Ddoor);  // attaches the servo on GIO2 to the servo object 
  myServoWindow.attach(Dwindow);  // attaches the servo on GIO2 to the servo object 
  rtc.begin();
  timer.setInterval(2000L, myTimerEvent);
  timer.setInterval(1000L, checkStt);
  timer.setInterval(2000L, lightProcess);
  
}



void processTimer(uint8_t Dpin, int stt1, int Vpin, int stt2){
  digitalWrite(Dpin, stt1);
  Blynk.virtualWrite(Vpin, stt2);
}
void myTimerEvent(){
  currentTime.hh = hour();
  currentTime.mm = minute();
  for (int i = 0 ; i < n; i ++){
   if ( currentTime.hh == timeInputStart[i].hh && currentTime.mm == timeInputStart[i].mm )
    {
      processTimer(Dpin[i], LOW, Vpin[i], LOW);
      timeInputStart[i].hh = -1;
      timeInputStart[i].mm = -1;
      Blynk.virtualWrite(V40,((String(i) +"Begin.hh: "+String(timeInputStart[i].hh)+" Begin.mm: "+String(timeInputStart[i].mm))));
    }
   if ( currentTime.hh == timeInputStop[i].hh && currentTime.mm == timeInputStop[i].mm )
   {
      processTimer(Dpin[i], HIGH, Vpin[i], HIGH);
      timeInputStop[i].hh = -1;
      timeInputStop[i].mm = -1;
      Blynk.virtualWrite(V40,((String(i) +"Stop.hh: "+String(timeInputStop[i].hh)+" Stop.mm: "+String(timeInputStop[i].mm))));
      Blynk.virtualWrite(VdisplayTimer[i]," ");
   }
      
  } 
}

void checkStt() {
 
  for (int i = 0; i < 4; i ++)
    x[i] = digitalRead(led[i]);
  for (int i = 0; i < 3; i ++)
  y[i] = digitalRead(Ddivice[i]);//quat

  b ="The temperature:"+String(t)+"°C. \The humidity\: "+String(h)+"%. \The gas concentration\ "+String(g) +
  ". \Light in Living Room\: " +stt[x[0]] +". \Light in Kitchen\: " +stt[x[2]] +  ". \Lights in Bedroom\: " +stt[x[1]] +   ". \Lights in Bath Room\: " +stt[x[3]] +
  ". \Fan\: "+stt[y[0]]+ ". \Heater\: " + stt[y[1]] + ". \Air conditioner\: " + stt[y[2]] + ". \The door is\ " + state[z[0]] + ". \The window is\ " + state[z[1]];  
}
BLYNK_WRITE(VlightRes) {
  lightThresh = asInt;

}

void lightProcess() {
  int lightStatus = analogRead(lightSensor);
  
  if (lightStatus < lightThresh) {
    digitalWrite(DledYard,LOW);
    Blynk.virtualWrite(VledYard,LOW);
    Blynk.virtualWrite(VlightDisplay,String(lightStatus) + " - " + "Dark");  
  }
  else {
    digitalWrite(DledYard,HIGH);
    Blynk.virtualWrite(VledYard,HIGH);
    Blynk.virtualWrite(VlightDisplay,String(lightStatus) + " - " + "Light");
  }
}

void loop()
{
  Blynk.run();
  timer.run();
}

