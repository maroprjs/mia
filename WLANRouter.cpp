/*
 * WLANRouter.cpp
 *
 *  Created on: 26.06.2021
 *      Author: maro
 */

#include "WLANRouter.h"

WLANRouter::WLANRouter(LatchingRelay* pwr) {
	_pwr = pwr;
    _routerIsOff = true;

}

void WLANRouter::begin(){
	turnOff();
}

void WLANRouter::loop(){
	//placeholder
}
void WLANRouter::turnOn(){
	Serial.println("_pwr->on()");
	_routerIsOff = false;

}
void WLANRouter::turnOff(){
	Serial.print("_pwr->off()");
	_routerIsOff = true;

}

void WLANRouter::toggle(){
	if (_routerIsOff){
		turnOn();
	}else{
		turnOff();
	};
}

WLANRouter::~WLANRouter() {
	// TODO Auto-generated destructor stub
}

