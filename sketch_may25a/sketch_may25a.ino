#include "EthernetInput.h"
Time Time;
uint32_t TimeInitEth, TimeGetDate;
bool ethState, error;
bool MonthDay, statePrevention;

#include "OnPrevention.h"
onPrevention onPrevention(10);     //10 секунд выдержка комманды открыть и закрыть
String datePrevention1 = "06-10";  //месяц и день для проведения 1 обслуживания
String datePrevention2 = "06-07";  //месяц и день для проведения 2 обслуживания

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
button ButtonValve1(A6, 6);  //Кнопка открыть/закрыть Kitchen, время ожидания
button ButtonValve2(A7, 6);  //Кнопка открыть/закрыть Bathroom, время ожидания


uint32_t i;
uint32_t T1;
bool Attempt;

#include "Control.h"
control start(30);  //длительность подачи питания на открытие или закрытия крана

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
  if (!ethState && !error) {
    if (!Time.Ethernetinit()) {
      ethState = 1;
      Serial.println("ok");
      Attempt = false;
    } else {
      Serial.println("Ethernetinit ERROR");
      ethState = true;
      error = true;
      Attempt = false;
    }
  }

  if (ethState) {
    if (millis() - TimeGetDate >= 1000 && !error) {
      TimeGetDate = millis();
      if (!Time.linkStatus()) {
        Serial.println("error = true");
        error = true;
      }
      if (!error) {
        Prevention();
        onPrevention.run();
      }
    }
    if (error) {
      if (timer() && !Attempt) {
        ethState = false;
        error = false;
        Attempt == true;
      }
    }
    start.buttons();
    start.AutoKitchen();
    start.AutoBathroom();
    start.Signals();
    start.Voice();
  }
  //Serial.println(analogRead(A6));
}
void Prevention() {
  Time.Update();
  TimeGetDate = millis();
  String Split;
  String formattedDate;
  formattedDate = Time.getDate();
  //Serial.println(formattedDate);
  int splitT = formattedDate.indexOf("-");
  Split = formattedDate.substring(splitT + 1, formattedDate.length() - 0);  //месяц и день
  if ((Split == datePrevention1) || (Split == datePrevention2)) {
    //Serial.println(Split);
    MonthDay = true;
  }
  if (MonthDay) {
    formattedDate = Time.getTime();
    splitT = formattedDate.indexOf(":");
    Split = formattedDate.substring(0, splitT);  //час
    if (Split == "12") {
      if (!statePrevention) {//запуск профилактики 
        onPrevention.start();
        statePrevention = true;
        Serial.println("12342313");  //выполнение профилактики
      }
    }
  }
  if (statePrevention) { //Обнуляем цикл профилактики
    formattedDate = Time.getDate();
    splitT = formattedDate.indexOf("-");
    Split = formattedDate.substring(splitT + 1, formattedDate.length() - 0);  //месяц и день
    Serial.println("Prevention ok");
    if (Split != datePrevention1) {
      statePrevention = false;
      MonthDay = false;
      Serial.println("!!!!!!");
    }
  }
}
bool timer() {
  if (millis() - T1 >= 1000) {
    T1 = millis();
    i++;
    Serial.println("Attempt to start the network via 60 dey or 43200 sec.");
    Serial.println(i);
    if (i >= 7200) {
      i = 0;
      return true;
    }
  }
  return false;
}