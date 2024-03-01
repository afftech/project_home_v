#include "Print.h"
#define S1 6
#define S2 7
#define S3 8
#define S4 9
class Voice {
public:
  voice() {
    pinMode(S1, OUTPUT);  //открыть кухню
    pinMode(S2, OUTPUT);  //закрыть кухню
    pinMode(S3, OUTPUT);  //открыть кухню
    pinMode(S4, OUTPUT);  //закрыть кухню
    //подтянуто к минусу
    digitalWrite(S1, false);
    digitalWrite(S2, false);
    digitalWrite(S3, false);
    digitalWrite(S4, false);
  }
  void process() {
    if (PlayState) {
      if (timer()) {
        digitalWrite(S1, false);
        digitalWrite(S2, false);
        digitalWrite(S3, false);
        digitalWrite(S4, false);
        PlayState = false;
      }
    }
  }
  bool Play(int i) {
    Serial.print(F("Voice:"));
    Serial.println(i);
    i = i - 1;
    digitalWrite(S1, SoundSelection[i][0]);
    digitalWrite(S2, SoundSelection[i][1]);
    digitalWrite(S3, SoundSelection[i][2]);
    digitalWrite(S4, SoundSelection[i][3]);
    PlayState = true;
    T1 = millis();
    return true;
  }
  bool timer() {
    if (millis() - T1 >= 1200) {
      Serial.println("millis() - T1");
      Serial.println(millis() - T1);
      return true;
    }
    return false;
  }
private:
  int SoundSelection[15][4]{
    //S1,S2,S3,S4
    { 1, 0, 0, 0 },  //1) Пришел сигнал с датчика протечки кухня (Сообщение: Сработала система контроля протечки, краны будут закрыты. Для открытия кранов в ручном режиме нажмите на кнопку в... )
    { 0, 1, 0, 0 },  //2) Нажата кнопка в кухне (Сообщение нажата кнопка управления кранами или звуковой сигнал "пик")
    { 1, 1, 0, 0 },  //3) После удержания 3 сек в кухне  или ванной подан сигнал на закрытие кранов (Сообщение: Краны будут закрыты, Система переходит  в режим пролива гидра затворов)
    { 0, 0, 1, 0 },  //4) Снятие сигнала закрытия кранов в кухне (прошло 60 секунд реле закрытия отключается) (Сообщение краны закрыты)
    { 1, 0, 1, 0 },  //5) После удержания 3х сек в кухне подан сигнал на открытия кранов из состояния  (закрыты и ждут 2 недели для пролива гидра затвора) (за это время протечек не было) ( Сообщение:  Протечек не было обнаружено, краны будут открыты.)
    { 0, 1, 1, 0 },  //6)  После удержания 3х сек в кухне подан сигнал на открытия кранов из состояния  (закрыты и ждут 2 недели для пролива гидра затвора, но что то протекло) (за это время протечки БЫЛИ) ( Сообщение:  Недавно были обнаружены протечки, но краны будут открыты.)
    { 1, 1, 1, 0 },  //7) Снятие сигнала открытия кранов в кухне (Сообщение краны открыты)
    { 0, 0, 0, 1 },  //8) Открытие в аварийном режиме после нажатия кнопки 3 сек. (Сработали  датчики протечки, и пока не просохло, нажата кнопка 3 сек и краны будут открыты вручную.) (Сообщение: Краны открыты в ручном режиме, Система продолжит работу, после высыхания.)
    { 1, 0, 0, 1 },  //9)
    { 0, 1, 0, 1 },  //10)
    { 1, 1, 0, 1 },  //11)
    { 0, 0, 1, 1 },  //12)
    { 1, 0, 1, 1 },  //13)
    { 0, 1, 1, 1 },  //14) Время и дата успешно обновлены после включения
    { 1, 1, 1, 1 }   //15) Не удалось обновить время и дату, после включения.
  };
  bool PlayState;
  long T1;
};