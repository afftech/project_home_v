
#include <curtains_control.h>
class Curtains {
public:
  Curtains(int x) {  //255 MAX
    this->numberCurtains = x;
    for (int i = 0; i < this->numberCurtains; i++) { curtainsObj[i] = new CurtainsObj(i + 1); }
  }

  void loop() {
    for (int addres = 0; addres < numberCurtains; addres++) {
      curtainsObj[addres]->loop();
      //this->state = curtainsObj[addres]->getState();
    }

    if (curtainsObj[addres_Pos]->State() == 1) {
      curtainsObj[addres_Pos]->send_and_receiv();
    } else {
      addres_Pos++;
      if (addres_Pos == numberCurtains) {
        addres_Pos = 0;
      }
    }
  }

  void send(int addres, char message) {
    state = SEND_DATA;
    addres = addres - 1;
    Serial.print(addres);
    Serial.print(":");
    switch (message) {
      /*case 'p':
        curtainsObj[addres]->setterBlinds(data);
        break;*/
      case 's':
        Serial.println("stop");
        curtainsObj[addres]->Stop();
        break;
      case 'u':
        Serial.println("open");
        curtainsObj[addres]->setterBlinds(99);
        break;
      case 'd':
        Serial.println("close");
        curtainsObj[addres]->setterBlinds(0);
        break;
      default:
        break;
    }
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
  uint32_t Time_Wait;
  int addres_Pos = 0;
  int numberCurtains = 1;
  CurtainsObj* curtainsObj[32];  // Изменить
  byte bytesCount = 0;
  byte incomingData[INCOMING_BYTES_COUNT];
  byte state = WAIT_DATA;
  byte commandToSend;

  unsigned long lastLevelRequest = 0;
};