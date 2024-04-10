
#include <Serial_master.h>
HardwareSerial Serial2(PB11, PB10);
Serial_master serial_master;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial2.begin(9600);
}
void loop() {
  serial_master.Listner();
}
