class Control {
public:
  void init() {
    pinMode(FanToilet1, OUTPUT);
    pinMode(FanToilet2, OUTPUT);
    pinMode(FanToilet3, OUTPUT);
    pinMode(FanToilet4, OUTPUT);
    pinMode(FanKitchen1, OUTPUT);
    pinMode(FanKitchen2, OUTPUT);
    pinMode(FanKitchen3, OUTPUT);
    pinMode(FanKitchen4, OUTPUT);
    pinMode(FanBathroom1, OUTPUT);
    pinMode(FanBathroom2, OUTPUT);
    pinMode(FanBathroom3, OUTPUT);
    pinMode(FanBathroom4, OUTPUT);
  }
  void RangeHood(bool RangeHoodspeed1, bool RangeHoodspeed2, bool RangeHoodspeed3) {
    if (RangeHoodspeed1) {
      Serial.println("1 speed");
    }
  }
};