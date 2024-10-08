#include "index.h"

void MyProgram::_setup(void) {
	Serial.begin(9600);
	stepper.setSpeed(10);
	// rtc.begin();
}

void MyProgram::main(void) {
	for (const auto listTime : this->List_Time) {
		if ((unsigned long) (millis() - this->LastTimeRTC) >= 1000) {
			this->LastTimeRTC = millis();
			Serial.println(rtc.getDayOfWeek());
			Serial.print(F("Date : "));
			Serial.println(rtc.datestr());
			Serial.print(F("Time : "));
			Serial.println(rtc.timestr());
			Serial.println();
			
			if (rtc.timestr() == listTime) {
				this->stateStepper = true;
				this->LastTimeStepper = millis();
			}
		}
	}
	
	if (this->stateStepper && (unsigned long) (millis() - this->LastTimeStepper) <= 3000) {
		stepper.step(360);
	}
	
	if (this->stateStepper && 
	   (unsigned long) (millis() - this->LastTimeStepper) > 6000 && 
	   (unsigned long) (millis() - this->LastTimeStepper) <= 9000)
	{
		stepper.step(-360);
		this->stateStepper = false;
	}
	
	delay(50);
}

void MyProgram::debbugStepper(void) {
	const int degress = 180;
	stepper.step(degress);
	delay(1500);
	stepper.step(-degress);
	delay(10000);

}