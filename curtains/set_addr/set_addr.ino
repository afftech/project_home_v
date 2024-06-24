HardwareSerial Serial2(PB11, PB10);

byte command[] = { 0x55, 0x00, 0x00, 0x02, 0x00, 0x02, 0x01, 0x01, 0x00, 0x00 };
byte command1[] = { 0x55, 0x01, 0x01, 0x03, 0x01, 0x00, 0xB9, 0x24 };

#define UP 0x01
#define DOWN 0x02


#define BtnGroupTime1 200  //программная задержка от помех для кликов
#define BtnGroupTime2 390  //время для средней длинны нажатия
#define BtnGroupTime3 500  //время для длинного нажатия
#include "button.h"

Button N_1(PA0, 1);
Button N_2(PA1, 1);
Button N_3(PA2, 1);
Button N_4(PA3, 1);
Button N_5(PA4, 1);
bool state;
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial.println("Start");
}
void install(byte Number);
void loop() {
  N_1.check();
  N_2.check();
  N_3.check();
  N_4.check();
  N_5.check();
  if (N_1.click()) {
    install(1);
  }
  if (N_2.click()) {
    install(2);
  }
  if (N_3.click()) {
    install(3);
  }
  if (N_4.click()) {
    install(4);
  }
  if (N_5.click()) {
    install(5);
  }
  available();
}
void available() {
  while (Serial2.available() > 0) {
    byte One = Serial2.read();
    Serial.print(One, HEX);
  }
}
void install(byte Number) {
  Serial.println();
  command[7] = Number;
  byte len = 10;
  word crc = modbus_crc16(command, 8);
  command[8] = lowByte(crc);
  command[9] = highByte(crc);
  // put your setup code here, to run once:
  Serial.print("OUTPUT:");
  for (byte i = 0; i < len; i++) {
    Serial2.write(command[i]);
  }
  for (byte i = 0; i < len; i++) {
    Serial.print(command[i], HEX);
  }
  Serial.println();
}
void DOWN_Start(byte Number) {
  Serial.println();
  state = !state;
  command1[2] = Number;
  if (state) {
    command1[4] = UP;
    Serial.print("UP:");
  } else {
    command1[4] = DOWN;
    Serial.print("DOWN:");
  }
  //command[6] = Number;
  byte len = 8;
  word crc = modbus_crc16(command1, 6);
  command1[6] = lowByte(crc);
  command1[7] = highByte(crc);
  // put your setup code here, to run once:
  Serial.print("OUTPUT:");
  for (byte i = 0; i < len; i++) {
    Serial2.write(command1[i]);
  }
  for (byte i = 0; i < len; i++) {
    Serial.print(command1[i], HEX);
  }
  Serial.println();
}
word modbus_crc16(byte* buf, int len) {
  word crc = 0xFFFF;

  for (int pos = 0; pos < len; pos++) {
    crc ^= (word)buf[pos];          // XOR byte into least sig. byte of crc
    for (int i = 8; i != 0; i--) {  // Loop over each bit
      if ((crc & 0x0001) != 0) {    // If the LSB is set
        crc >>= 1;                  // Shift right and XOR 0xA001
        crc ^= 0xA001;
      } else        // Else LSB is not set
        crc >>= 1;  // Just shift right
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  return crc;
}