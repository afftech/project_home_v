#include "EthernetInput.h"
Time Time;
uint32_t TimeInitEth, TimeGetDate;
bool ethState;
bool MonthDay, statePrevention;


//#define print Serial.println

#define DataSensor1 A0
#define DataSensor2 A1
#define DataSensor3 A2
#define DataSensor4 A3
#define DataSensor5 A4
#define DataSensor6 A5

#define Valve1Open 2
#define Valve1Close 3
#define Valve2Open 4
#define Valve2Close 5

#include "button.h"
button ButtonValve1(A6);  //Кнопка открыть
button ButtonValve2(A7);  //Кнопка открыть


int i;
#include "Control.h"
control start;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(DataSensor1, INPUT);
  pinMode(DataSensor2, INPUT);
  pinMode(DataSensor3, INPUT);
  pinMode(DataSensor4, INPUT);
  pinMode(DataSensor5, INPUT);
  pinMode(DataSensor6, INPUT);
  pinMode(Valve1Open, OUTPUT);
  pinMode(Valve1Close, OUTPUT);
  pinMode(Valve2Open, OUTPUT);
  pinMode(Valve2Close, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!ethState) {
    // if (millis() - TimeInitEth >= 3000) {
    if (!Time.Ethernetinit()) {
      ethState = 1;
      Serial.println("ok");
    }
    // }
  }
  Prevention();
  start.buttons();
  start.AutoKitchen();
  start.AutoBathroom();
  start.Signals();
  start.Voice();
  //Serial.println(analogRead(A6));
}
void Prevention() {
  if (ethState) {
    if (millis() - TimeGetDate >= 3000) {
      TimeGetDate = millis();
      String Split;
      String formattedDate;
      formattedDate = Time.getDate();
      int splitT = formattedDate.indexOf("-");
      Split = formattedDate.substring(splitT + 1, formattedDate.length() - 0);  //месяц и день
      if (Split == "06-07") {
        //Serial.println(Split);
        MonthDay = true;
      }
      if (MonthDay) {
        formattedDate = Time.getTime();
        splitT = formattedDate.indexOf(":");
        Split = formattedDate.substring(0, splitT);  //час
        if (Split == "23") {
          if (!statePrevention) {
            //запуск профилактики
            statePrevention = true;
            Serial.println("12342313");  //выполнение профилактики
          }
        }
      }
      if (statePrevention) {
        formattedDate = Time.getDate();
        splitT = formattedDate.indexOf("-");
        Split = formattedDate.substring(splitT + 1, formattedDate.length() - 0);  //месяц и день
        Serial.println("Prevention ok");
        if (Split != "06-07") {
          statePrevention = false;
          MonthDay = false;
          Serial.println("!!!!!!");
        }
      }
    }
  }
}
