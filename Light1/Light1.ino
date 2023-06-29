#define RangeHood1_461 A0  //413 RangeHood1_461 и RangeHood2_816  приходят одновременно
#define RangeHood2_816 A0
#define RangeHood3_460 A1

#define ToiletBtn_461 A2
#define ToiletLight_816 A2

#define FanToilet1 6  //////4 скорости
#define FanToilet2 7
#define FanToilet3 8
#define FanToilet4 9

#define BathroomBtn_461 A3
#define BathroomLight_816 A2

#define FanBathroom1 10  //////4 скорости
#define FanBathroom2 11
#define FanBathroom3 12
#define FanBathroom4 13


#define KitchenBtn_815 A1

#define FanKitchen1 2  //////4 скорости
#define FanKitchen2 3
#define FanKitchen3 4
#define FanKitchen4 5


void setup() {
  Serial.begin(9600);
  pinMode(BathroomBtn_461, INPUT);
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
  // put your setup code here, to run once:
}

void loop() {
  digitalWrite(FanKitchen4, true);
  Serial.println(analogRead(BathroomBtn_461));
  delay(500);
  // put your main code here, to run repeatedly:
}
