//первый мотор
bool LR_State_Manual;
int LR_OldState;
bool LR_Stop;
void loop_LR() {
  Open_LR.check();
  Close_LR.check();

  if (Open_LR.click()) {
    if (LR_OldState == 0) {
      Curtains.send(1, 'd');
      LR_OldState = 1;
      Serial.println("Open");
    } else if (LR_OldState != 0) {
      Curtains.send(1, 's');
      LR_OldState = 0;
      Serial.println("O_Stop1");
    }
  }
  if (Close_LR.click()) {
    if (LR_OldState == 0) {
      Curtains.send(1, 'd');
      LR_OldState = 2;
      Serial.println("Close");
    } else if (LR_OldState != 0) {
      Curtains.send(1, 's');
      LR_OldState = 0;
      Serial.println("C_Stop1");
    }
  }

  if (Open_LR.hold2()) {
    Curtains.send(1, 's');
    LR_OldState = 0;
    Serial.println("O_Stop2");
  }
  if (Close_LR.hold2()) {
    LR_OldState = 0;
    Curtains.send(1, 's');
    Serial.println("C_Stop2");
  }
}