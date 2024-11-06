//моторы 4 и 5

bool BR_Btn_Open, BR_Btn_Close, ModInstall, OldState, StateInstall = 0, StateInstallBTN;
int state_btn;
uint32_t BR_Tmr_Open, BR_Tmr_Close, holdModInstall;
void PlayBR(char message);
void InstallModOn() {
  if (StateInstall & millis() - holdModInstall >= 10000) {
    StateInstall = 0;
    ModInstall = !ModInstall;
    Serial.print("StateInstall:");
    Serial.println(ModInstall);
    Curtains.send(1, 'm', ModInstall);
    Curtains.send(2, 'm', ModInstall);
    Curtains.send(3, 'm', ModInstall);
    Curtains.send(4, 'm', ModInstall);
    Curtains.send(5, 'm', ModInstall);
  }
  StateInstallBTN = (Open_BR.stateBtn() & Close_BR.stateBtn());
  if (StateInstallBTN != OldState) {
    OldState = StateInstallBTN;
    if (StateInstallBTN) {
      StateInstall = true;
      holdModInstall = millis();
    } else {
    }
  }
}
void loop_BR() {
  Open_BR.check();
  Close_BR.check();
  select_BR_4.check();
  select_BR_5.check();
  InstallModOn();
  //длинное удержание 2х клавишь напрпр вкл реж прогр. Далее в реж репев мотор м наж кнопку в нужном помещ
  if (select_BR_4.click() && !select_BR_5.click()) {  //две клавиши для упр. чем управлять
    state_btn = 1;                                    // едет 1
  } else if (!select_BR_4.click() && select_BR_5.click()) {
    state_btn = 2;  // едет 2
  } else if (select_BR_4.click() && select_BR_5.click()) {
    state_btn = 3;  // едут оба
  } else {
    state_btn = 3;  // едут оба
  }

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
  if (millis() - BR_Tmr_Open >= 100) {
    if (BR_Btn_Close) {
      PlayBR('s');  //стоп
      BR_Btn_Close = false;
    } else {
      PlayBR('d');
    }
    BR_Btn_Open = false;
  }
  if (millis() - BR_Tmr_Close >= 100) {
    if (BR_Btn_Open) {
      PlayBR('s');  //стоп
      BR_Btn_Open = false;
    } else {
      PlayBR('u');
    }
    BR_Btn_Close = false;
  }
  if (Open_BR.hold2() || Open_BR.hold1()) {
    PlayBR('s');  //стоп
  }
  if (Close_BR.hold2() || Close_BR.hold2()) {
    PlayBR('s');
  }
  //Serial.println(select_BR_4.click());
}
void PlayBR(char message) {
  if (state_btn == 1) {  // для 4 //едет
    Curtains.send(4, message, 0);
  }
  if (state_btn == 2) {  // для 5
    Curtains.send(5, message, 0);
  }
  if (state_btn == 3) {  // для 4 и 5
    Curtains.send(4, message, 0);
    Curtains.send(5, message, 0);
  }
}
