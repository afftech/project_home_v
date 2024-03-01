#include "OnPrevention2.h"
class strait {
public:
  strait(char pin_Open, char pin_Close) {
    _pin_Open = pin_Open;
    _pin_Close = pin_Close;
  }
  void loop() {
    _onPrevention2.run();
    if (FunActiv != OldStartActiv) {
      OldStartActiv = FunActiv;
      if (OldStartActiv) {
        StartActiv = 1;
        Serial.println("_onPrevention2.run();");
      }
    }
    if (StartActiv) {
      if (millis() - TimerStrait >= 1000) {  //сутки 86400000 мили сек
        day++;
        TimerStrait = millis();
        if (day == 14) {           //суток
          _onPrevention2.start();  //проливаем воду
          Serial.println("_onPrevention2.start();");
          day = 0;
          StartActiv = 0;
        }
      }
    }
  }
  void set_State(bool i) {
    FunActiv = i;
  }
private:
  char _pin_Open, _pin_Close;
  onPrevention2 _onPrevention2{ 60, _pin_Open, _pin_Close };  //10 секунд выдержка комманды открыть и закрыть
  bool FunActiv, StartActiv, OldStartActiv;
  unsigned long TimerStrait;
  int day;
};