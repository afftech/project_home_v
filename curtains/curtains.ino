#include <curtains_RS485.h>
Curtains Curtains(5);
#define BtnGroupTime1 300  //программная задержка от помех для кликов
#define BtnGroupTime2 490  //время для средней длинны нажатия
#define BtnGroupTime3 600  //время для длинного нажатия

#include <button.h>
#include <Serial_slave.h>
SerialSlave Slave;

Button Open_LR(PB0, 1);   //PB5
Button Close_LR(PA7, 1);  //PB8

Button Open_MR(PA6, 1);   //PB9
Button Close_MR(PA5, 1);  //PA0

Button Open_K(PA4, 1);   //PA1
Button Close_K(PA3, 1);  //PA2

Button Open_BR(PA2, 1);   //PA3
Button Close_BR(PA1, 1);  //PA4

Button select_BR_4(PA0, 0);  //PA5
Button select_BR_5(PB9, 0);  //PA6

#include <Little_Room.h>
#include <Middle_Room.h>
#include <Big_Room.h>
#include <Kitchen.h>

HardwareSerial Serial2(PB11, PB10);
//Serial_master serial_master;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
}
void loop() {
  Slave.Listner();
  loop_LR();
  loop_MR();
  loop_BR();
  loop_K();
  Curtains.loop();
}