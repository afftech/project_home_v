#include <curtains_RS485.h>
Curtains Curtains(5);
#define BtnGroupTime1 200  //программная задержка от помех для кликов
#define BtnGroupTime2 390  //время для средней длинны нажатия
#define BtnGroupTime3 500  //время для длинного нажатия
#include <button.h>


Button Open_LR(PB5, 1);
Button Close_LR(PB8, 1);

Button Open_MR(PB9, 1);
Button Close_MR(PA0, 1);

Button Open_K(PA1, 1);
Button Close_K(PA2, 1);

Button Open_BR(PA3, 1);
Button Close_BR(PA4, 1);

Button select_BR_4(PA5, 0);
Button select_BR_5(PB6, 0);

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
  loop_LR();
  loop_MR();
  loop_BR();
  loop_K();
  Curtains.loop();
}