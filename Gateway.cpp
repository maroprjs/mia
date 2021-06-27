/*
 * Gateway.cpp
 *
 *  Created on: 26.06.2021
 *      Author: maro
 */

#include "Gateway.h"

Gateway::Gateway(LatchingRelay* pwr) {
	_pwr = pwr;
    _gatewayIsOff = true;
    _countDownStepMillis = 0;
	_countDown = STARTUP_COUNTDOWN;
	_countDownEnabled = false;

}

void Gateway::begin(){
	turnOff();
}

void Gateway::loop(){

	if (_countDownEnabled == true){
		if (_countDown > 0 ){
		   if ((_countDownStepMillis + COUNTDOWN_TIME) < millis()){
              _countDown--;
              _countDownStepMillis = millis();
		   }
		}else {
			turnOff();
			stopCountDown();
		}
	}

	if (Serial5.available()){
		//if stop countdown
		Serial.write(Serial5.read());
		//stopCountDown();
		//startCountDown(SHUTDOWN_COUNTDOWN);

	}
}
void Gateway::turnOn(){
	Serial.println("gw _pwr->on()");
	//_pwr->on();
	_gatewayIsOff = false;
    startCountDown(STARTUP_COUNTDOWN);
}

void Gateway::turnOff(){
	Serial.println("gw _pwr->off()");
	//_pwr->off();
	_gatewayIsOff = true;

}

void Gateway::toggle(){
	if (_gatewayIsOff){
		turnOn();
	}else{
		turnOff();
	};
}

void Gateway::startCountDown(unsigned long countdown){
	_countDownStepMillis = millis();
	_countDown = countdown;
    _countDownEnabled = true;
}

void Gateway::stopCountDown(){
    _countDownEnabled = false;
}

Gateway::~Gateway() {
	// TODO Auto-generated destructor stub
}

