#include <curtains_RS485.h>
Curtains Curtains(1);
class Serial_master {
public:
  void Listner() {  // пример 55 00 00 02 00 02 01 01 9D 58
    if (Serial.available() > 0) {
      char key = Serial.read();
      int data = Serial.parseInt();
      if (key != ' ') {
        controlDevice(key, data);
      }
    }
    Curtains.loop();
  }
private:
  void controlDevice(char key, int data) {
    switch (key) {
      case 'p':
        break;
      case 's':
        Curtains.send(1, 's');
        break;
      case 'u':
        Curtains.send(1, 'u');
        break;
      case 'd':
        Curtains.send(1, 'd');
        break;
      default:
        break;
    }
    //Serial.print(key);
    //Serial.println(data);
  }
};