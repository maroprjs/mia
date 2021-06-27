/*
 * Gateway.h
 *
 *  Created on: 26.06.2021
 *      Author: maro
 */

#ifndef GATEWAY_H_
#define GATEWAY_H_
#include "LatchingRelay.h"
#define STARTUP_COUNTDOWN 780 //13min
#define SHUTDOWN_COUNTDOWN 180 //3min
#define COUNTDOWN_TIME 1000 //ms
class Gateway {
public:
	Gateway(LatchingRelay* pwr);
	void begin();
	void loop();
	void turnOn();
	void turnOff();
	void toggle();
	virtual ~Gateway();
private:
    void startCountDown(unsigned long countdown);
    void stopCountDown();
	LatchingRelay* _pwr;
	bool _gatewayIsOff;
	unsigned long _countDownStepMillis;
	unsigned long _countDown;
	bool _countDownEnabled;


};

#endif /* GATEWAY_H_ */
