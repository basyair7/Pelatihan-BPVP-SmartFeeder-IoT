#include "Arduino.h"
#include "Stepper.h"
#include "DS3231rtc.h"

#define STEPS 2048

class MyProgram {
public:
    static MyProgram& instance() {
        static MyProgram instance;
        return instance;
    }

    static void setup() {
        instance()._setup();
    }

    static void loop() {
        // instance().test1();
        instance().test2();
        // instance().test3();
    }

private:
    void _setup(void);
    void test1(void);
    void test2(void);
    void test3(void);

    float stepsToDegress(int number_of_steps, int degrees) {
        return (float)number_of_steps * ((float)degrees / 360.0);
    }

private:
    const int16_t PINOUT_STEPPER[4] = {8,10,11,9};
    Stepper* stepper = new Stepper(
        STEPS, 
        PINOUT_STEPPER[0], 
        PINOUT_STEPPER[1], 
        PINOUT_STEPPER[2], 
        PINOUT_STEPPER[3]
    );
    DS3231rtc rtc;
    int hour, minute, second;
    String timestr;

private:
    unsigned long LastTimeRTC = 0;
    unsigned long LastTimeStepperUP = 0, LastTimeStepperDown = 0;
    bool stateStepperUP = false, stateStepperDown = false;
    bool stateStepper = false;
};