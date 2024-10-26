//мотор 2
//не раб стоп на кн закр
bool MR_Btn_Open, MR_Btn_Close;
uint32_t MR_Tmr_Open, MR_Tmr_Close;
void loop_MR() {
  Open_MR.check();
  Close_MR.check();
  if (Open_MR.click()) {
    MR_Btn_Open = true;
  }
  if (Close_MR.click()) {
    MR_Btn_Close = true;
  }
  if (!MR_Btn_Open) {
    MR_Tmr_Open = millis();
  }
  if (!MR_Btn_Close) {
    MR_Tmr_Close = millis();
  }
  if (millis() - MR_Tmr_Open >= 200) {
    if (MR_Btn_Close) {
      Curtains.send(2, 's', 0);
      Serial.println("MR_Stop0");
      MR_Btn_Close = false;
    } else {
      Curtains.send(2, 'u', 0);
      Serial.println("MR_Open");
    }
    MR_Btn_Open = false;
  }
  if (millis() - MR_Tmr_Close >= 200) {
    if (MR_Btn_Open) {
      Curtains.send(2, 's', 0);
      Serial.println("MR_Stop1");
      MR_Btn_Open = false;
    } else {
      Curtains.send(2, 'd', 0);
      Serial.println("MR_Close");
    }
    MR_Btn_Close = false;
  }
  if (Open_MR.hold2()) {
    Curtains.send(2, 's', 0);
    Serial.println("MR_Stop2");
  }
  if (Close_LR.hold2()) {
    Curtains.send(2, 's', 0);
    Serial.println("MR_Stop3");
  }
}