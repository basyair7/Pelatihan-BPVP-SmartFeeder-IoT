#include "Arduino.h"
#include "Stepper.h"

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
            instance().test1();
        }

    private:
        void _setup(void);
        void test1(void);

        float stepsToDegress(int number_of_steps, int steps) {
            return map(steps, 0, 360, 0, number_of_steps);
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
};