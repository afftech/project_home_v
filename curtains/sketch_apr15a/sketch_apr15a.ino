
HardwareSerial Serial2(PB11, PB10);
byte Number = 1;  //номер сюда впиши
byte command[] = { 0x55, 0x00, 0x00, 0x02, 0x00, 0x02, 0x01, 0x01, 0x9D, 0x58 };
void setup() {
  command[6] = Number;
  Serial.begin(9600);
  Serial2.begin(9600);
  byte len = 10;
  // put your setup code here, to run once:
  for (byte i = 0; i < len; i++) {
    Serial.print(command[i], HEX);
    Serial2.write(command[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
