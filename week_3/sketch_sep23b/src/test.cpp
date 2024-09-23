#include "index.h"

void MyProgram::_setup() {
    Serial.begin(9600);
    rtc.begin();
    stepper->setSpeed(10);
}

void MyProgram::test1() {
    Serial.println(rtc.getDayOfWeek());
    Serial.println(rtc.datestr());
    Serial.println(rtc.timestr());
    Serial.println();
    delay(500);
}

void MyProgram::test2() {
    unsigned long currentTime = millis();

    if ((unsigned long) (currentTime - this->LastTimeRTC) >= 1000) {
        this->LastTimeRTC = currentTime;
        rtc.time(&this->hour, &this->minute, &this->second);
        Serial.println(rtc.getDayOfWeek());
        Serial.print(F("Date : "));
        Serial.println(rtc.datestr());
        Serial.print(F("Time : "));
        Serial.println(rtc.timestr());
        Serial.println();

        if (this->hour == 13 && this->minute == 20 && this->second == 0) {
            this->stateStepper = true;
            this->LastTimeStepperUP = currentTime;
        }
    }

    if (this->stateStepper && millis() - this->LastTimeStepperUP <= 3000) {
        stepper->step(this->stepsToDegress(STEPS, 180));
    }

    if (this->stateStepper && millis() - this->LastTimeStepperUP > 6000 && millis() - this->LastTimeStepperUP <= 9000) {
        stepper->step(-this->stepsToDegress(STEPS, 180));
        this->stateStepper = false;
    }
}