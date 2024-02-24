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

#include "Voice.h"
Voice voice;

//Кнопка реагирует через 6 секунд
#define BtnGroupTime1 200   //программная задержка от помех для кликов
#define BtnGroupTime2 390   //время для средней длинны нажатия
#define BtnGroupTime3 6000  //время для длинного нажатия

#include "button.h"
Button ButtonValve1(A6, 1);  //Кнопка открыть/закрыть Kitchen, режим кнопки
Button ButtonValve2(A7, 1);  //Кнопка открыть/закрыть Bathroom, режим кнопки

#include "Control.h"
control control(30);  //длительность подачи питания на открытие или закрытия крана


bool ethState, error;            //состояние сетевого подключения, состояние протечки
bool MonthDay, statePrevention;  //Регистр состояния получения месяца и запуска профилактики

#include "OnPrevention.h"
onPrevention onPrevention(30);     //10 секунд выдержка комманды открыть и закрыть
String datePrevention1 = "06-18";  //месяц и день для проведения 1 обслуживания
String datePrevention2 = "06-07";  //месяц и день для проведения 2 обслуживания

#include "ControlEthernet.h"

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
  voice.process();  //перенести в ino
  ControlEth_loop();
}
