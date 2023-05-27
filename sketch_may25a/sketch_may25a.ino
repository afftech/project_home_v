#include "button.h"


#define print Serial.println

#define DataSensor1 A0
#define DataSensor2 A1
#define DataSensor3 A2
#define DataSensor4 A3
#define DataSensor5 A4
#define DataSensor6 A5

#define Valve1Open 2
#define Valve1Close 3
#define Valve2Open 4
#define Valve2Close 5

button ButtonValve1(A6);  //Кнопка открыть
button ButtonValve2(A7);  //Кнопка открыть



bool Valve2State, SignalKitchen, SignalBathroom, CurrentStateKitchen;

unsigned long Timer1;
int Valve1State;
int increment, i;

#include "Control.h"
control start;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(DataSensor1, INPUT);
  pinMode(DataSensor2, INPUT);
  pinMode(DataSensor3, INPUT);
  pinMode(DataSensor4, INPUT);
  pinMode(DataSensor5, INPUT);
  pinMode(DataSensor6, INPUT);

  pinMode(Valve1Open, OUTPUT);
  pinMode(Valve1Close, OUTPUT);
  pinMode(Valve2Open, OUTPUT);
  pinMode(Valve2Close, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  start.buttons();
  start.AutoKitchen();
  start.Signals();
  //Serial.println(analogRead(A6));
}





