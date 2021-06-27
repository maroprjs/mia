/*
 * Gateway.h
 *
 *  Created on: 26.06.2021
 *      Author: maro
 */

#ifndef GATEWAY_H_
#define GATEWAY_H_
#include "LatchingRelay.h"

class Gateway {
public:
	Gateway(LatchingRelay* pwr);
	void toggle();
	virtual ~Gateway();
};

#endif /* GATEWAY_H_ */
