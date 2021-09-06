/*
 * MiaUI.cpp
 *
 *  Created on: 02.09.2021
 *      Author: user
 */

#include "MiaUI.h"

MiaUI::MiaUI(GsmModem *modem, Gateway *gw, WLANRouter *wlanRouter, Eltako * eltako, VictronCharger* charger) {
	_gsm = modem;
	_gw = gw;
	_wlanRouter = wlanRouter;
	_lastCall = 0;
	_eltako = eltako;
	_charger = charger;
	_chargerRawDataPublished = "";
	_chargerRawDataCurrent = "";
	_lastPublished = 0;

}

void MiaUI::begin(){
	_lastCall = millis();
	_lastPublished = millis();

}

void MiaUI::loop(){
	if (_gsm->sms->newMsgArrived){/*defined in base class "subscriber"*/
		//processSMS(swInfo);
		String reply = "";
	    String cmd = "";
		_gsm->sms->newMsgArrived = false;//message read
		cmd = _gsm->sms->msg;
		//Serial.println(cmd);
		if (mmi(cmd)){
			_gsm->sms->receiver = _gsm->sms->sender;
			_gsm->sms->msg = cmd;
			//_gsm->sendSMS(_gsm->sms);
		}
	    _gsm->delAllSms(_gsm->sms);//from device buffer
	}
	if (millis() > _lastCall + ONE_DAY){
		_gsm->reset();
		_gsm->sms->receiver = SUBSCRIBER_NUMBER;
		_gsm->sms->msg = "reseted!";
		//_gsm->sendSMS(_gsm->sms);
		_lastCall = millis();

	}
	if (millis() > _lastPublished + PUBLISH_INTERVAL){
		_publishDeltas();
		_lastPublished = millis();
	}
}

/*************
 * mmi function - handle command from sms
 *
 * status of all below objects will be saved in separate variables and published when changed, separatly
 *
 */
bool MiaUI::mmi(String cmd){ //return indicates if command is recognized
	bool retVal = true;
	cmd = cmd.trim();
	cmd = cmd.toLowerCase();
	if (cmd == "main on"){
		if (_eltako->isOff()){
		   _eltako->toggle();Serial.println("Eltako was On, toggle off");
		}
	}else if (cmd == "main off"){
		if (_eltako->isOn()){
		   _eltako->toggle();Serial.println("Eltako was Off, toggle on");
		}
	}else if (cmd == "wlan on"){
		_wlanRouter->turnOn(); Serial.println("wlan on");
	}else if (cmd == "wlan off"){
		_wlanRouter->turnOff(); Serial.println("wlan off");
	}else if (cmd == "gw on"){
		_gw->turnOn();
		_gw->stopShutDown(); Serial.println("gw on");
	}else if (cmd == "gw off"){
		_gw->turnOff(); Serial.println("gw off");
	}else if (cmd == "weather"){ //ws2300

	}else if (cmd == "victron"){ //victron values
		_chargerRawDataCurrent =_charger->getRawData(); Serial.println("victron raw");
    _lastPublished = millis();
    //_gsm->sms->msg =_charger->getRawData(); Serial.println("victron raw");
    //_gsm->sendSMS(_gsm->sms);
    Serial.println(_chargerRawDataCurrent);
	}else if (cmd == "efoy"){ //efoy values

	}else{
		retVal = false;
	}

	return retVal;
}

//////////////////private///////////////////////////

void MiaUI::_publishDeltas(){
	//bi-state objects:
	 //TODO
	//victron:
	if (_chargerRawDataPublished != _chargerRawDataCurrent){
		//receiver is last requestor
		_gsm->sms->msg = _chargerRawDataCurrent;
		_gsm->sendSMS(_gsm->sms);
    Serial.print("pubi1: ");
    Serial.println(_chargerRawDataPublished);
		_chargerRawDataPublished = _chargerRawDataCurrent;
    Serial.print("pubi2: ");
    Serial.println(_chargerRawDataPublished);
	}


}

MiaUI::~MiaUI() {
	// TODO Auto-generated destructor stub
}