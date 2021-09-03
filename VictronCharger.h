/*
 * VictronCharger.h
 *
 *  Created on: 03.09.2021
 *      Author: user
 */

#ifndef VICTRONCHARGER_H_
#define VICTRONCHARGER_H_

#include "Arduino.h"
#include "VeDirectFrameHandler.h"


#define VICTRON_SERIAL Serial3

class VictronCharger {
public:
	VictronCharger();
	void begin();
	void loop();
	String  getRawData();
	virtual ~VictronCharger();

private:
	void _readVEData();
	boolean _isNumeric(char chStr[]);

private:
	VeDirectFrameHandler * _myve;
	unsigned long _data_count;
};

#endif /* VICTRONCHARGER_H_ */
