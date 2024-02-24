#include "EthernetInput.h"
Time Time;
uint32_t TimeGetDate;  //интервал получения данных из сети
uint32_t i;
uint32_t T1;
bool Attempt;
bool OldError;  //что бы убрать бесконечное повторение звука
bool timer();
void Prevention();
void ControlEth_loop() {
  // put your main code here, to run repeatedly:
  if (!ethState && !error) {
    if (!Time.Ethernetinit()) {
      ethState = 1;
      Serial.println("ok");
      Attempt = false;
    } else {
      Serial.println("Ethernetinit ERROR");
      ethState = true;
      error = true;
      Attempt = false;
      voice.Play(15);  //ошибка сети
    }
  }

  if (ethState) {
    if (millis() - TimeGetDate >= 1000 && !error) {
      TimeGetDate = millis();
      if (!Time.linkStatus()) {
        Serial.println("error = true");
        error = true;
        voice.Play(15);  //ошибка сети
      } else {
        voice.Play(14);  //вребя обновлено
      }
      if (!error) {
        Prevention();
        onPrevention.run();
      }
    }
    if (error) {
      if (timer() && !Attempt) {
        ethState = false;
        error = false;
        Attempt == true;
      }
    }
    control.buttons();
    control.AutoKitchen();
    control.AutoBathroom();
    control.Signals();
    //control.Voice(); перенесли в .ino
  }
  if (OldError != error) {
    if (error) {
      voice.Play(15);  //ошибка сети
    } else {
      voice.Play(14);  //ошибка сети
    }
    OldError = error;
  }
  //Serial.println(analogRead(A6));
}
void Prevention() {
  Time.Update();
  TimeGetDate = millis();
  String Split;
  String formattedDate;
  formattedDate = Time.getDate();
  //Serial.println(formattedDate);
  int splitT = formattedDate.indexOf("-");
  Split = formattedDate.substring(splitT + 1, formattedDate.length() - 0);  //месяц и день
  if ((Split == datePrevention1) || (Split == datePrevention2)) {
    //Serial.println(Split);
    MonthDay = true;
  }
  if (MonthDay) {
    formattedDate = Time.getTime();
    splitT = formattedDate.indexOf(":");
    Split = formattedDate.substring(0, splitT);  //час
    if (Split == "15") {
      if (!statePrevention) {  //запуск профилактики
        onPrevention.start();
        statePrevention = true;
        Serial.println("statePrevention = true;");  //выполнение профилактики
      }
    }
  }
  if (statePrevention) {  //Обнуляем цикл профилактики
    formattedDate = Time.getDate();
    splitT = formattedDate.indexOf("-");
    Split = formattedDate.substring(splitT + 1, formattedDate.length() - 0);  //месяц и день
    Serial.println("Prevention ok");
    if ((Split != datePrevention1) && (Split != datePrevention2)) {
      statePrevention = false;
      MonthDay = false;
      Serial.println("!!!!!!");
    }
  }
}

bool timer() {
  if (millis() - T1 >= 1000) {
    T1 = millis();
    i++;
    Serial.println("Attempt to start the network via 7200 sec.");
    Serial.println(i);
    if (i >= 7200) {
      i = 0;
      return true;
    }
  }
  return false;
}