#include <curtains_control.h>
class Curtains {
public:
  Curtains(int x) {  //255 MAX
    this->numberCurtains = x;
    for (int i = 0; i < this->numberCurtains; i++) { curtainsObj[i] = new CurtainsObj(i + 1); }
  }

  void loop() {

    switch (state) {
      case WAIT_DATA:
        //getDataFromUART();
        break;
      case SEND_DATA:
        state = WAIT_DATA;
        break;
    }
    for (int addres = 0; addres < numberCurtains; addres++) {
      curtainsObj[addres]->loop();
      //this->state = curtainsObj[addres]->getState();
    }
  }
  void send(int addres, char message) {
    state = SEND_DATA;
    addres = addres - 1;
    switch (message) {
      /*case 'p':
        curtainsObj[addres]->setterBlinds(data);
        break;*/
      case 's':
        curtainsObj[addres]->Stop();
        break;
      case 'u':
        curtainsObj[addres]->setterBlinds(99);
        break;
      case 'd':
        curtainsObj[addres]->setterBlinds(0);
        break;
      default:
        break;
    }
    Serial.println("Start");
  }
  void getDataFromUART() {
    byte incomingBytesRead = 0;
    while (Serial2.available() > 0) {
      incomingData[incomingBytesRead++] = Serial2.read();
      ;
      //delay(5);
    }
    if (incomingBytesRead) {
      bytesCount = incomingBytesRead;
      state = PARSING_DATA;
    }
  }
private:
  int numberCurtains = 1;
  CurtainsObj* curtainsObj[32];  // Изменить
  byte bytesCount = 0;
  byte incomingData[INCOMING_BYTES_COUNT];
  byte state = WAIT_DATA;
  byte commandToSend;

  unsigned long lastLevelRequest = 0;
};