#include "STM32_CAN.h"

static CAN_message_t CAN_outMsg_1;
static CAN_message_t CAN_inMsg;

//отправка в шину SendData(0x1A4, 0x0102);
STM32_CAN Can(CAN1, ALT, RX_SIZE_64, TX_SIZE_16);


void CAN_Setup() {
  Can.begin();
  Can.setBaudRate(500000);  //500KBPS
  Can.setMBFilterProcessing(MB0, 0x1A5, 0x1FFFFFFF);
  Can.setMBFilterProcessing(MB1, 0x1A6, 0x1FFFFFFF);
}

void SendData(uint32_t id, uint16_t DATA) {  //отправка в шину SendData(0x1A4, 0x0102);
  CAN_outMsg_1.id = id;
  CAN_outMsg_1.len = 2;
  for (int i = 0, pos = 1; i < 2; i++) {
    CAN_outMsg_1.buf[pos--] = DATA & 0xFF;
    DATA >>= 8;
  }
  // Only the counter value is updated to the 3 messages sent out.
  Can.write(CAN_outMsg_1);
}