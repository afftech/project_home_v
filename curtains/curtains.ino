#include <botton.h>
#include <Little_Room.h>
#include <Middle_Room.h>
#include <Big_Room.h>
#include <Kitchen.h>

Button Open_LR(PB5, 1);
Button Close_LR(PB8, 1);

Button Open_MR(PB9, 1);
Button Close_MR(PA0, 1);

Button Open_K(PA1, 1);
Button Close_K(PA2, 1);

Button Open_BR(PA3, 1);
Button Close_BR(PA4, 1);

Button select_BR_4(PA5, 1);
Button select_BR_5(PB6, 1);

HardwareSerial Serial2(PB11, PB10);
Serial_master serial_master;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
}
void loop() {
  Open_LR.check();
  Close_LR.check();
  Open_MR.check();
  Close_MR.check();
  Open_K.check();
  Close_K.check();
  Open_BR.check();
  Close_BR.check();
  select_BR_4.check();
  select_BR_5.check();
  loop_LR();
  loop_MR();
  loop_BR();
  loop_K();
}