
#include <Serial_master.h>
HardwareSerial Serial2(PB11, PB10);
Serial_master serial_master;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start");
  Serial2.begin(9600);
}
//char key = 's';
void loop() {
  // put your main code here, to run repeatedly:
  serial_master.Listner();
  //setterBlinds(99);
}
