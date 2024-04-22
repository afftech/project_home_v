// мотор три
void loop_K() {
  Open_K.check();
  Close_K.check();
  if (Open_K.click()) {
    Curtains.send(3, 'd');
  }
  if (Open_K.hold2()) {
    Curtains.send(3, 's');
  }
  if (Close_K.click()) {
    Curtains.send(3, 'u');
  }
  if (Close_K.hold2()) {
    Curtains.send(3, 's');
  }
}