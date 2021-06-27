/*
 * LatchingRelay.cpp
 *
 *  Created on: 26.06.2021
 *      Author: maro
 */

#include "LatchingRelay.h"

LatchingRelay::LatchingRelay(uint8_t setPin, uint8_t resetPin) {
	_setPin = setPin;
	_resetPin = resetPin;
	_onRequested = false;
	_offRequested = false;
	_transitionStartTime = 0;
	_switchingState = IDLE;

}

void LatchingRelay::begin() {
	pinMode(_setPin, OUTPUT);
	pinMode(_resetPin, OUTPUT);
	digitalWrite(_setPin, LOW);
	digitalWrite(_resetPin, LOW);
}

void LatchingRelay::loop() {
	if ((_onRequested == true) && (_switchingState == IDLE)){
		_switchingState = TRANSITION;
		digitalWrite(_setPin, HIGH);
		_transitionStartTime = millis();
	}
	if ((_offRequested == true) && (_switchingState == IDLE)){
		_switchingState = TRANSITION;
		digitalWrite(_resetPin, HIGH);
		_transitionStartTime = millis();
	}

	if (_switchingState == TRANSITION){
		if (millis() > (_transitionStartTime + LATCHING_RELAY_TRANSITION_TIME)){
			digitalWrite(_setPin, LOW);
			digitalWrite(_resetPin, LOW);
			_onRequested = false;
			_offRequested = false;
			_switchingState = IDLE;
		}
	}
}

void LatchingRelay::on() {
	_onRequested = true;

}

void LatchingRelay::off() {
	_offRequested = true;

}

LatchingRelay::~LatchingRelay() {
	// TODO Auto-generated destructor stub
}

