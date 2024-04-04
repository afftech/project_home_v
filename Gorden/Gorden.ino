#include <Gorden.h>
HardwareSerial Serial2(PB11, PB10);
bool StationState;
#include <Serial_master.h>
Serial_master Serial_master;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  delay(500);
  // put your main code here, to run repeatedly:
  Serial_master.Listner();
  //setterBlinds(99);
  loop_Gorden();
}
