/*СПИСОК ФУНКЦИЙ
  SendData(0x1B2, 0x0101); //выкл всю кухню 
  SendData(0x1B2, 0x0102); //вкл всю кухню 
*/
void can_Control(uint32_t id, uint8_t* DATA) {  // управление контролллером

  switch (id) {
    case 0x1B2:           //адрес отправителя
      switch (DATA[0]) {  //команда
        case 1:
          switch (DATA[1]) {  //значение
            case 1:
              digitalWrite(A2, true);
              break;
            case 2:
              digitalWrite(A2, false);
              break;
          }
          break;
      }
      break;
    case 0x1A6:           //адрес отправителя
      switch (DATA[0]) {  //команда
        case 1:
          switch (DATA[1]) {  //значение
            case 1:
              digitalWrite(A3, true);
              break;
            case 2:
              digitalWrite(A3, false);
              break;
          }
          break;
      }
      break;
  }
  delete[] DATA;
}

uint8_t* Receiving() {  //Чтение из шины
  uint8_t* DATA = new uint8_t[2];
  //We only read data from CAN bus if there is frames received, so that main code can do it's thing efficiently.
  //Serial.print("Channel:");
  //Serial.print(CAN_inMsg.id, HEX);
  if (CAN_inMsg.flags.remote == false) {  //если нет удаленного запроса
    for (int i = 0; i < CAN_inMsg.len; i++) {
      DATA[i] = CAN_inMsg.buf[i];
      //Serial.print("0x");
      //Serial.print(DATA[i], HEX);  //выводим значение в формате hex
      //if (i != (CAN_inMsg.len - 1)) Serial.print(" ");
    }
  } else {
    Serial.println(" Data: REMOTE REQUEST FRAME");
  }
  can_Control(CAN_inMsg.id, DATA);
  return DATA;
}
void loop_CAN_Net() {
  while (Can.read(CAN_inMsg)) {
    Receiving();
  }
}