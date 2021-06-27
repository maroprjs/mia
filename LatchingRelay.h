/*
 * LatchingRelay.h
 *
 *  Created on: 26.06.2021
 *      Author: maro
 */

#ifndef LATCHINGRELAY_H_
#define LATCHINGRELAY_H_
#include "Arduino.h"

#define LATCHING_RELAY_TRANSITION_TIME 300 //ms

class LatchingRelay {
	enum SwitchingState{
			IDLE,
			TRANSITION
		};
public:
	LatchingRelay(uint8_t setPin, uint8_t resetPin);
	void begin();
	void loop();
	void on();
	void off();
	virtual ~LatchingRelay();

private:
	uint8_t _setPin;
	uint8_t _resetPin;
	bool _onRequested;
	bool _offRequested;
	uint32_t _transitionStartTime;
	SwitchingState _switchingState;
};

#endif /* LATCHINGRELAY_H_ */
