#include "Arduino.h"
#include "Stepper.hpp"
#include "DS3231rtc.hpp"

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
        instance().main();
    }

private:
    void _setup(void);
	void main(void);

private:
	const String List_Time[3] = {"7:15:0", "15:30:0", "20:0:0"};
    const int16_t PINOUT_STEPPER[4] = {8,10,11,9};
    MyStepper stepper = MyStepper(
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
    unsigned long LastTimeRTC = 0, LastTimeStepper = 0;
	bool stateStepper = false;
};