//моторы 4 и 5

bool BR_Btn_Open, BR_Btn_Close;
uint32_t BR_Tmr_Open, BR_Tmr_Close;
void PlayBR(char message);
void loop_BR() {
  Open_BR.check();
  Close_BR.check();
  select_BR_4.check();
  select_BR_5.check();

  if (Open_BR.click()) {
    BR_Btn_Open = true;
  }
  if (Close_BR.click()) {
    BR_Btn_Close = true;
  }
  if (!BR_Btn_Open) {
    BR_Tmr_Open = millis();
  }
  if (!BR_Btn_Close) {
    BR_Tmr_Close = millis();
  }
  if (millis() - BR_Tmr_Open >= 200) {
    if (BR_Btn_Close) {
      PlayBR('s');
      BR_Btn_Close = false;
    } else {
      PlayBR('d');
    }
    BR_Btn_Open = false;
  }
  if (millis() - BR_Tmr_Close >= 200) {
    if (BR_Btn_Open) {
      PlayBR('s');
      BR_Btn_Open = false;
    } else {
      PlayBR('u');
    }
    BR_Btn_Close = false;
  }
  if (Open_BR.hold2()) {
    PlayBR('s');
  }
  if (Close_BR.hold2()) {
    PlayBR('s');
  }
  //Serial.println(select_BR_4.click());
}
void PlayBR(char message) {
  if (select_BR_4.click() && !select_BR_5.click()) {  // для 4
    Serial.print("For:");
    Serial.print(4);
    Serial.print(";");
    Curtains.send(4, message);
  } else if (!select_BR_4.click() && select_BR_5.click()) {  // для 5
    Serial.print("For:");
    Serial.print(5);
    Serial.print(";");
    Curtains.send(5, message);
  } else if (select_BR_4.click() && select_BR_5.click()) {  // для 4 и 5
    Serial.print("For:");
    Serial.print("4 and 5");
    Serial.print(";");
    Curtains.send(4, message);
    Curtains.send(5, message);
  }
  Serial.print("message:");
  Serial.println(message);
}