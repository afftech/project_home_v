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
  }
private:
  void controlDevice(char key, int data) {
    switch (key) {
      case 'p':
        setterBlinds(data);
        break;
      case 's':
        Stop();
        break;
      case 'u':
        setterBlinds(99);
        break;
      case 'd':
        setterBlinds(0);
        break;
      default:
        break;
    }
    Serial.println(data);
  }
};