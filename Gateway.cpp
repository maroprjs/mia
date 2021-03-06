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
	_countDown = LONG_COUNTDOWN;
	_shutdownOngoing = false;
	_lastCmd = "";

}

void Gateway::begin(){
	GATEWAY_SERIAL.begin(9600);
	//Serial.println("gw _pwr->off()");
	//_pwr->off();
	//startShutDown(LONG_COUNTDOWN); //<-better to shut it down in a controlled way, in case gw is used for programming
}

void Gateway::loop(){
	byte ch;
	if (_shutdownOngoing == true){ //requires serial listener on real gateway
		if (_countDown > 0 ){
		   if ((_countDownStepMillis + COUNTDOWN_TIME) < millis()){
              _countDown--;
              _countDownStepMillis = millis();
		   }
		}
		if (_countDown <= SHORT_COUNTDOWN ){ //sends request to real gw to shutdown
			GATEWAY_SERIAL.println("shutdown"); //TODO: is it okay to send every sec or should I add flag?
		}
		if (_countDown <= 0 ){
			//Serial.println("gw _pwr->off()");
			_pwr->off();
			_gatewayIsOff = true;
			stopShutDown();
		}
	}

	if (GATEWAY_SERIAL.available()){
		ch = GATEWAY_SERIAL.read();
		_lastCmd += (char)ch;
		if (ch=='\n') {
			_lastCmd.trim();
			//if stop countdown
			Serial.println(_lastCmd);
			GATEWAY_SERIAL.println(_lastCmd); //mirror
			//TODO:
			if (_lastCmd == "stop_shutdown"){
			   stopShutDown();
			};
			if (_lastCmd == "start_shutdown"){
			   startShutDown(SHORT_COUNTDOWN);
			};
			_lastCmd = "";
		}


	}
}
void Gateway::turnOn(){
	//Serial.println("gw _pwr->on()");
	_pwr->on();
	_gatewayIsOff = false;
    //startShutDown(LONG_COUNTDOWN); //if triggered by wlan btn, gw not needed, should shutdown by itself, but cronjob doesnt start serial listener,
	                                 //hence gw shuts down abruptly
	                                 //TODO: check cronjob or find another way
}

void Gateway::turnOff(){
	if (_shutdownOngoing == false){
		startShutDown(SHORT_COUNTDOWN);
	}
}

void Gateway::toggle(){
	if (_gatewayIsOff){
		turnOn();
	}else{
		turnOff();
	};
}

void Gateway::startShutDown(unsigned long countdown){
	_countDownStepMillis = millis();
	_countDown = countdown;
    _shutdownOngoing = true; //from now on shutdown handled in loop function
}

void Gateway::stopShutDown(){
    _shutdownOngoing = false;

}

Gateway::~Gateway() {
	// TODO Auto-generated destructor stub
}

