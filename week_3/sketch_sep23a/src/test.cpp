#include "index.h"

int previous = 0;
const int stepsPerRevolution = STEPS;

void MyProgram::_setup(void) {
    Serial.begin(9600);
    stepper->setSpeed(10);
}

void MyProgram::test1(void) {
    
}