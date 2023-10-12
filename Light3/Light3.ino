//8 переключателей
#define LitleRoom_LitleRBra A0    //1:519-523  2:834-839 12:473-476
#define MiddleRoom_MiddleRBra A1  //1:520-523  2:833-837 12:474-477
#define Loggia_Toilet A2          //1:519-522  2:833-837 12:472-475
#define Bathroom_Miror A3
#define Sensor A4
// 12 выходов
#define MiddleRoomLight1 2
#define MiddleRoomLight2 3
#define MiddleRoomLight3 4
#define MiddleRoomBra 11

#define RibbonWBrightly 5
#define LitleRoomLight1 6
#define LitleRoomLight2 7

#define LitleBraLRLight3 8
#define ToiletLight 9
#define BathroomLight 10


#define LoggiaLight 12
#define BathMirorLight 13

#define TimeOffDT 90  //Время в секундах выключения управления освещением комнаты

#include "ButtonGroup.h" /* Максимум 1s*/
ButtonGroup BtnGroup0(LitleRoom_LitleRBra, 1, 1, 1023, 521, 836, 474);
ButtonGroup BtnGroup1(MiddleRoom_MiddleRBra, 1, 1, 1023, 521, 836, 474);
ButtonGroup BtnGroup2(Loggia_Toilet, 1, 1, 1023, 521, 836, 475);
ButtonGroup BtnGroup3(Bathroom_Miror, 1, 1, 1023, 521, 836, 475);
ButtonGroup BtnGroup4(Sensor, 1, 1, 1023, 521, 836, 475);

#include "Little_Room.h"
Little_Room little_Room;
#include "Middle_Room.h"
Middle_Room middle_Room;

void setup() {
  // put your setup code here, to run once:
  pinMode(MiddleRoomLight1, OUTPUT);
  pinMode(MiddleRoomLight2, OUTPUT);
  pinMode(MiddleRoomLight3, OUTPUT);
  pinMode(RibbonWBrightly, OUTPUT);
  pinMode(LitleRoomLight1, OUTPUT);
  pinMode(LitleRoomLight2, OUTPUT);
  pinMode(LitleBraLRLight3, OUTPUT);
  pinMode(ToiletLight, OUTPUT);
  pinMode(BathroomLight, OUTPUT);
  pinMode(MiddleRoomBra, OUTPUT);
  pinMode(LoggiaLight, OUTPUT);
  pinMode(BathMirorLight, OUTPUT);

  Serial.begin(9600);
}
void loop() {
  little_Room.run();
  middle_Room.run();
  // put your main code here, to run repeatedly:
  BtnGroup0.check();
  BtnGroup1.check();
  BtnGroup2.check();
  BtnGroup3.check();
  BtnGroup4.check();
  {  //малая комната
    if (BtnGroup0.click1()) {
      Serial.println("click1 LitleRoomLight");
      little_Room.clickLitleRoom();
    }
    if (BtnGroup0.hold1_2()) {
      Serial.println("hold1_2 LitleRoomLight Off");
      little_Room.OffRoom();
    }
    if (BtnGroup0.click2()) {
      Serial.println("click2 LitleRBra");
      little_Room.ClickLitleRBra();
    }
    if (BtnGroup0.hold2_2()) {
      Serial.println("hold2_2 LitleRBra Off");
      little_Room.OffRoom();
    }
  }
  {  //средняя комната
    if (BtnGroup1.click1()) {
      Serial.println("click1 MiddleRoomLight");
      middle_Room.clickRoom();
    }
    if (BtnGroup1.hold1_2()) {
      Serial.println("hold1_2 MiddleRoomLight Off");
      middle_Room.OffRoom();
    }
    if (BtnGroup1.click2()) {
      Serial.println("click2 MiddleRoomBra");
      middle_Room.ClickBra();
    }
    if (BtnGroup1.hold2_2()) {
      Serial.println("hold2_2 MiddleRoomBra Off");
      middle_Room.OffRoom();
    }
  }
}
