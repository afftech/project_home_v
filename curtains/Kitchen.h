// мотор три

bool K_Btn_Open, K_Btn_Close;
uint32_t K_Tmr_Open, K_Tmr_Close;
void loop_K() {
  Open_K.check();
  Close_K.check();
  if (Open_K.click()) {
    K_Btn_Open = true;
  }
  if (Close_K.click()) {
    K_Btn_Close = true;
  }
  if (!K_Btn_Open) {
    K_Tmr_Open = millis();
  }
  if (!K_Btn_Close) {
    K_Tmr_Close = millis();
  }
  if (millis() - K_Tmr_Open >= 200) {
    if (K_Btn_Close) {
      Curtains.send(3, 's',0);
      Serial.println("K_Stop0");
      K_Btn_Close = false;
    } else {
      Curtains.send(3, 'u', 0);
      Serial.println("K_Open");
    }
    K_Btn_Open = false;
  }
  if (millis() - K_Tmr_Close >= 200) {
    if (K_Btn_Open) {
      Curtains.send(3, 's', 0);
      Serial.println("K_Stop1");
      K_Btn_Open = false;
    } else {
      Curtains.send(3, 'd', 0);
      Serial.println("K_Close");
    }
    K_Btn_Close = false;
  }
  if (Open_K.hold2()) {
    Curtains.send(3, 's', 0);
    Serial.println("K_Stop2");
  }
  if (Close_LR.hold2()) {
    Curtains.send(3, 's', 0);
    Serial.println("K_Stop3");
  }
}