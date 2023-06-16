#include "HardwareSerial.h"
#include "Arduino.h"

class onPrevention {
public:
 onPrevention(int waiting_time){
_waiting_time = waiting_time;
 }
  bool run() {
    if(on){
        if(!close){
        digitalWrite(Valve1Close,true);
        digitalWrite(Valve2Close,true);
        if(time1()){
            close = true;
            digitalWrite(Valve1Close,false);
            digitalWrite(Valve2Close,false);
        }
        }
        if(close && !open){
        digitalWrite(Valve2Open,true);
        digitalWrite(Valve1Open,true);
        if(time1()){
            open = true;
            on = false;
            digitalWrite(Valve2Open,true);
            digitalWrite(Valve1Open,true);
        }
        }
       
    }
  }

  void start(){
    on = true;
    Timer = millis();
  }
private:
    bool on, open, close;
    unsigned long Timer;
  int i;
  int _waiting_time;
  bool time1(bool v) {
    if (v) {
      if (millis() - Timer >= 1000) {
        i++;
        Timer = millis();
        Serial.println(i);
        if (i >= _waiting_time) {
          i = 0;
          return true;
        } else {
          return false;
        }
      }
      return false;
    } else {
      i = 0;
      return false;
    }
  }
};