//#include <Gorden.h>

#include <curtains_RS485.h>
HardwareSerial Serial2(PB11, PB10);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  //setterBlinds(99);

}
