#include "Arduino.h"

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
  const uint16_t TRIGGER_PINS[2] = { 7, 9 };
  const uint16_t ECHO_PINS[2]    = { 6, 10 };
  const uint16_t LED_PINS[2]     = { 3, 4 };

private:
  void _setup(void);
  void test1(void);
  float getDistance(uint8_t triggerPin, uint8_t echoPin);

private:
  // flag untuk Sensor Ultrasonic
  bool sensorDetected1 = false, sensorDetected2 = false;
  bool incoming = false, outcoming = false;
  
};