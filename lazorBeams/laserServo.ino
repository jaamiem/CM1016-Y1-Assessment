#include <Servo.h>

Servo servHoriz;

void setup() {
  servHoriz.attach(10);
}

void loop() {
  servHoriz.write(700);
  delay(1000);

  servHoriz.write(1500);
  delay(1000);

  servHoriz.write(3500);
  delay(1000);
}

