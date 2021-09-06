/*
 * Eltako.cpp
 *
 *  Created on: 02.09.2021
 *      Author: user
 */

#include "Eltako.h"

Eltako::Eltako(uint8_t eltakoPin, uint8_t probePin) {
	_eltakoPin = eltakoPin;
	_probePin = probePin;
	_lastTimeRead = 0;
	_pobeCount4Avrg = 0;
	_accumulatedProbe4Avrg = 0;
	_currentProbeValue = 0;
	_eltakoIsOn = false;

}

void Eltako::begin(){
	pinMode(_eltakoPin, OUTPUT);
	pinMode(_probePin, INPUT);
	digitalWrite(_eltakoPin, HIGH);
	_lastTimeRead = millis();
}
void Eltako::loop(){

	if (millis() > _lastTimeRead + READ_INTERVAL){
		_accumulatedProbe4Avrg = _accumulatedProbe4Avrg + analogRead(_probePin);
		_pobeCount4Avrg++;
		if (_pobeCount4Avrg >= AVERAGE_COUNT){
			_currentProbeValue = _accumulatedProbe4Avrg / _pobeCount4Avrg;
      Serial.println(_currentProbeValue);
			_accumulatedProbe4Avrg = 0;
			_pobeCount4Avrg = 0;
		}
		_eltakoIsOn = ( _currentProbeValue > THRESHOLD) ? true : false;

		_lastTimeRead = millis();


	}


}

void Eltako::toggle(){
	digitalWrite(_eltakoPin, LOW);
	delay(500);
	digitalWrite(_eltakoPin, HIGH);
}

Eltako::~Eltako() {
	// TODO Auto-generated destructor stub
}
