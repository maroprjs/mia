/*
 * WLANRouter.h
 *
 *  Created on: 26.06.2021
 *      Author: maro
 */

#ifndef WLANROUTER_H_
#define WLANROUTER_H_
#include "LatchingRelay.h"

class WLANRouter {
public:
	WLANRouter(LatchingRelay* pwr);
	void begin();
	void loop();
	void turnOn();
	void turnOff();
	void toggle();
	virtual ~WLANRouter();
private:
	LatchingRelay* _pwr;
	bool _routerIsOff;
};

#endif /* WLANROUTER_H_ */
