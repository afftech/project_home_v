#include "OnPrevention2.h"

class strait : public onPrevention2 {
public:
  strait(int pin_Open, int pin_Close, unsigned long waiting_time)
    : onPrevention2() {
    this->pin_Open = pin_Open;
    this->pin_Close = pin_Close;
    this->waiting_time = waiting_time;
  }
  void loop() {
    onPrevention2::run();
    if (FunActiv != OldStartActiv) {
      OldStartActiv = FunActiv;
      if (OldStartActiv) {
        StartActiv = 1;
        day = 0;
      } else {
        StartActiv = 0;
      }
    }
    if (!FunActiv) {
      TimerStrait = millis();
    }
    if (StartActiv) {
      if (millis() - TimerStrait >= 1000) {  //сутки 86400000 мили сек
        day++;
        Serial.print("day:");
        Serial.println(day);
        TimerStrait = millis();
        if (day == 14) {           //суток
          onPrevention2::start();  //проливаем воду
          day = 0;
        }
      }
    }
  }
  void set_State(bool i) {
    FunActiv = i;
  }
private:
  bool FunActiv, StartActiv, OldStartActiv;
  unsigned long TimerStrait;
  int day;
};