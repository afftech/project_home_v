//первый мотор

bool LR_Btn_Open, LR_Btn_Close;
uint32_t LR_Tmr_Open, LR_Tmr_Close;
void loop_LR() {
  Open_LR.check();
  Close_LR.check();
  if (Open_LR.click()) {
    LR_Btn_Open = true;
  }
  if (Close_LR.click()) {
    LR_Btn_Close = true;
  }
  if (!LR_Btn_Open) {
    LR_Tmr_Open = millis();
  }
  if (!LR_Btn_Close) {
    LR_Tmr_Close = millis();
  }
  if (millis() - LR_Tmr_Open >= 200) {
    if (LR_Btn_Close) {
      Curtains.send(1, 's', 0);
      Serial.println("LR_Stop0");
      LR_Btn_Close = false;
    } else {
      Curtains.send(1, 'u', 0);
      Serial.println("LR_Open");
    }
    LR_Btn_Open = false;
  }
  if (millis() - LR_Tmr_Close >= 200) {
    if (LR_Btn_Open) {
      Curtains.send(1, 's', 0);
      Serial.println("LR_Stop1");
      LR_Btn_Open = false;
    } else {
      Curtains.send(1, 'd', 0);
      Serial.println("LR_Close");
    }
    LR_Btn_Close = false;
  }
  if (Open_LR.hold2()) {
    Curtains.send(1, 's', 0);
    Serial.println("LR_Stop2");
  }
  if (Close_LR.hold2()) {
    Curtains.send(1, 's', 0);
    Serial.println("LR_Stop3");
  }
}