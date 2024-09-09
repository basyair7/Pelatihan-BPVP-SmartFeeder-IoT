#include "index.h"

void setup() {
  // put your setup code here, to run once:
  HelloWorld::begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  HelloWorld::serialHelloWorld();
  HelloWorld::blink();
  // HelloWorld::pwm();
  // HelloWorld::SerialMessage();
}
