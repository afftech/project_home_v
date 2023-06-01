#include "EthernetInput.h"
Time Time;

void setup() {
  Time.Ethernetinit();
  // You can use Ethernet.init(pin) to configure the CS pin
  Serial.begin(115200);
}

void loop() {
  delay(1000);
  Serial.println(Time.getDate());
  delay(1000);
}
