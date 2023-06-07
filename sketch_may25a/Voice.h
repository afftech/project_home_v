
class voice {
public:
  voice() {
    pinMode(9, OUTPUT);
    digitalWrite(9, true);
  }
  bool OpenKitchen() {
    digitalWrite(9, false);
    delay(200);
    digitalWrite(9, true);
    print("123456789");
    return true;
  }
private:
};