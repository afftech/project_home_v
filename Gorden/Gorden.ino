HardwareSerial Serial2(PB11, PB10);
bool StationState;
#include <Serial_slave.h>
SerialSlave SerialSlave;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200);
  pinMode(PC13, OUTPUT);
}

void loop() {
  delay(500);
  SerialSlave.send("a", 1);
  // put your main code here, to run repeatedly:
  SerialSlave.Listner();

  digitalWrite(PC13, StationState);
}
