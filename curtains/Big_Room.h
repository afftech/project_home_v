//моторы 4 и 5

bool BR_Btn_Open, BR_Btn_Close;
int state_btn;
uint32_t BR_Tmr_Open, BR_Tmr_Close;
void PlayBR(char message);
void loop_BR() {
  Open_BR.check();
  Close_BR.check();
  select_BR_4.check();
  select_BR_5.check();

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
  if (millis() - BR_Tmr_Open >= 200) {
    if (BR_Btn_Close) {
      PlayBR('s');  //стоп
      BR_Btn_Close = false;
    } else {
      PlayBR('d');
    }
    BR_Btn_Open = false;
  }
  if (millis() - BR_Tmr_Close >= 200) {
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
    Curtains.send(4, message);
  }
  if (state_btn == 2) {  // для 5
    if (message == 's') {
      Curtains.send(5, 's');
    } else if (message == 'd') {
      Curtains.send(5, 'u');
    } else if (message == 'u') {
      Curtains.send(5, 'd');
    }
  }
  if (state_btn == 3) {  // для 4 и 5
    Curtains.send(4, message);
    if (message == 's') {
      Curtains.send(5, 's');
    } else if (message == 'd') {
      Curtains.send(5, 'u');
    } else if (message == 'u') {
      Curtains.send(5, 'd');
    }
  }
}