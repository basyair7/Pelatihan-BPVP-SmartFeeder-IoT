#pragma once

#include "Arduino.h"
#include "WiFiProgram.h"

class MyProgram {
public:
    static MyProgram& instance() {
        static MyProgram instance;
        return instance;
    }

    static void setup(void) {
        instance()._setup();
    }

    static void loop(void) {
        instance()._loop();
    }

private:
    void _setup(void);
    void _loop(void);
};
