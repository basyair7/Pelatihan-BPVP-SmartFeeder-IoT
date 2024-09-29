/*! @file main.cpp
 *  @version 1.0.0
*/

#include "main.h"

String Timer1, Timer2, Timer3;
bool auto_state, switch_state;
int capacity;

void MyProgram::__autoFeeder__(void) {
  if ((unsigned long) (millis() - this->LastTimeRTC) >= 1000) {
    this->LastTimeRTC = millis();
    Serial.println(this->rtc.getDayOfWeek());
    Serial.print(F("Date : "));
    Serial.println(this->rtc.datestr());
    Serial.print(F("Time : "));
    Serial.println(this->rtc.timestr());

    if (this->rtc.timestr() == Timer1 || this->rtc.timestr() == Timer2 || this->rtc.timestr() == Timer3) {
      this->stateStepper1 = true;
      this->LastTimeStepper1 = millis();
    }
  }

  if (this->stateStepper1 && (unsigned long)(millis() - this->LastTimeStepper1) <= 3000) 
  {
    this->stepper.step(DEGRESS_STEPPER);
  }

  if (this->stateStepper1 && (unsigned long)(millis() - this->LastTimeStepper1) > 6000 && (unsigned long)(millis() - this->LastTimeStepper1) <= 9000)
  {
    this->stepper.step(-DEGRESS_STEPPER);
    this->stateStepper1 = false;
  }
}

void MyProgram::__manualFeeder__(void) {
  if (this->stateStepper2 && (unsigned long)(millis() - this->LastTimeStepper2) <= 3000)
  {
    this->stepper.step(DEGRESS_STEPPER);
  }

  if (this->stateStepper2 && (unsigned long)(millis() - this->LastTimeStepper2) > 6000 && (unsigned long)(millis() - this->LastTimeStepper2) <= 9000)
  {
    this->stepper.step(-DEGRESS_STEPPER);
    this->stateStepper2 = false;
  }
}

void MyProgram::__monitor__(void) {
  if ((unsigned long)(millis() - this->LastTimeMonitor) >= 1000) {
    this->LastTimeMonitor = millis();

    Serial.print(F("AUTO : "));
    Serial.println(auto_state ? "Enable" : "Disable");
    Serial.print(F("Switch : "));
    Serial.println(switch_state ? "Open" : "Close");

    Serial.println();
    Serial.print(F("Capacity : "));
    Serial.print(capacity);
    Serial.println(F("%"));
    
    Serial.println();
  }
}

void MyProgram::__setup__(void) {
  Serial.begin(9600);
  // serialData.begin(9600);
  i2cSlave.begin();

  this->stepper.setSpeed(10);
  // this->rtc.begin();
}

void MyProgram::__main__(void) {
  // serialData.reqData();
  // serialData.getData(50);
  // serialData.getBlynkCmd(&auto_state, &switch_state);
  // serialData.getTimeAuto(&Timer1, &Timer2, &Timer3);
  // capacity = serialData.getCapacity();

  if (capacity >= 0) {
    if (auto_state) {
      this->__autoFeeder__();
    }

    if (!auto_state && switch_state) {
      this->LastTimeStepper2 = millis();
      this->stateStepper2 = true;
      this->__manualFeeder__();
    }
  }
  
  delay(50);
}

void MyProgram::__debug__() {
  // get data from nodemcu
  // serialData.reqData();
  // serialData.getData(50);
  // serialData.getBlynkCmd(&auto_state, &switch_state);
  // serialData.getTimeAuto(&Timer1, &Timer2, &Timer3);
  // capacity = serialData.getCapacity();

  i2cSlave.run();

  i2cSlave.getBlynkCmd(&auto_state, &switch_state);
  i2cSlave.getTimeAuto(&Timer1, &Timer2, &Timer3);
  capacity = i2cSlave.getCapacity();

  this->__monitor__();

  delayMicroseconds(50);
}
