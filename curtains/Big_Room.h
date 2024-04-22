//моторы 4 и 5
void loop_BR() {
  Open_BR.check();
  Close_BR.check();
  select_BR_4.check();
  select_BR_5.check();
  if (select_BR_4.click()) {
    if (Open_BR.click()) {
      Curtains.send(4, 'd');
    }
    if (Open_BR.hold2()) {
      Curtains.send(4, 's');
    }
    if (Close_BR.click()) {
      Curtains.send(4, 'u');
    }
    if (Close_BR.hold2()) {
      Curtains.send(4, 's');
    }
  }
  if (select_BR_5.click()) {
    if (Open_BR.click()) {
      Curtains.send(5, 'd');
    }
    if (Open_BR.hold2()) {
      Curtains.send(5, 's');
    }
    if (Close_BR.click()) {
      Curtains.send(5, 'u');
    }
    if (Close_BR.hold2()) {
      Curtains.send(5, 's');
    }
  }
}