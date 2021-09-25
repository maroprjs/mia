/*
 * Eltako.h
 *
 *  Created on: 02.09.2021
 *      Author: user
 */

#ifndef ELTAKO_H_
#define ELTAKO_H_
#include "Arduino.h"

#define READ_INTERVAL 1000
#define THRESHOLD  300 // 470k:100k
#define AVERAGE_COUNT 10

class Eltako {
public:
	Eltako(uint8_t eltakoPin, uint8_t probePin);
	void begin();
	void loop();
	bool isOn() {return _eltakoIsOn;};
	bool isOff() {return !_eltakoIsOn;};
	void toggle();
	virtual ~Eltako();
private:
	uint8_t _eltakoPin;
	uint8_t _probePin;
	int _accumulatedProbe4Avrg;
	int _currentProbeValue;
	uint32_t _lastTimeRead;
	uint8_t _pobeCount4Avrg;
	bool _eltakoIsOn;
};

#endif /* ELTAKO_H_ */
