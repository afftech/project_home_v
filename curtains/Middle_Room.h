//мотор 2
void loop_MR() {
  Open_MR.check();
  Close_MR.check();
  if (Open_MR.click()) {
    Curtains.send(2, 'd');
  }
  if (Open_MR.hold2()) {
    Curtains.send(2, 's');
  }
  if (Close_MR.click()) {
    Curtains.send(2, 'u');
  }
  if (Close_MR.hold2()) {
    Curtains.send(2, 's');
  }
}