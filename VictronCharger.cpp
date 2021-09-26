/*
 * VictronCharger.cpp
 *
 *  Created on: 03.09.2021
 *      Author: user
 */

#include "VictronCharger.h"
#include "VeDirectConfig.h"

VictronCharger::VictronCharger() {
	_myve = new VeDirectFrameHandler();
	_data_count = 0;
	_lastRead = 0;

}

void VictronCharger::begin(){
	 VICTRON_SERIAL.begin(19200);

}

void VictronCharger::loop(){
	//if (millis() > _lastRead + CHARGER_READ_INTERVAL){
		  // Receive information on Serial from MPPT
		  _readVEData();
		_lastRead = millis();
	//}

}

VictronCharger::~VictronCharger() {
	// TODO Auto-generated destructor stub
}

String  VictronCharger::getRawData() {
  String message = "";
 
  for ( int i = 0; i < _myve->veEnd; i++ ) {
    message += _myve->veName[i];
    message += ":";
    message += _myve->veValue[i];
    message += ";";
  };
  
  /*
  //message += _myve->veName[3]; //only voltage...long sms doesnt work properly (TODO)
  //message += ":";
  message += _myve->veValue[3];
  message += ";";
  //message += _myve->veName[7]; //only voltage...long sms doesnt work properly (TODO)
  //message += ":";
  message += _myve->veValue[7];
  //message += ";";
  //message += _myve->veName[11]; //only voltage...long sms doesnt work properly (TODO)
  //message += ":";
  //message += _myve->veValue[11];*/
  return message;
}

/* TODO: get charger values in readable format!!!!
String  VictronCharger::getBatVoltage(){
	float Batvoltage = 0;
	if (isNumeric(value[VE_V])) {
	  Batvoltage = (float) atoi(value[VE_V]) / 1000;
	}
}

String  VictronCharger::getBatCurrent(){
	float Batcurrent = 0;
	if (isNumeric(value[VE_I])) {
	  Batcurrent = (float) atoi(value[VE_I]) / 1000;
	}
}

String  VictronCharger::getBatChargingstate(){
	int ChargingState = 0;
	if (isNumeric(value[VE_CS])) {
	  ChargingState = (int) atoi(value[VE_CS]);
	}
}

String VictronCharger::getStringState(int cs) {
  switch (cs) {
    case CS_Off                       : return "Off"; break;
    case CS_Low_power                 : return "Low power"; break;
    case CS_Fault                     : return "Fault"; break;
    case CS_Bulk                      : return "Bulk"; break;
    case CS_Absorption                : return "Absorption"; break;
    case CS_Float                     : return "Float"; break;
    case CS_Storage                   : return "Storage"; break;
    case CS_Equalize_manual           : return "Equalize manual"; break;
    case CS_Inverting                 : return "Inverting"; break;
    case CS_Power_supply              : return "Power supply"; break;
    case CS_Starting_up               : return "Starting up"; break;
    case CS_Repeated_absorption       : return "Repeated absorption"; break;
    case CS_Auto_equalize_Recondition : return "Auto equalize Recondition"; break;
    case CS_BatterySafe               : return "BatterySafe"; break;
    case CS_External_Control          : return "External Control"; break;
    default                           : return "Unknown state (" + String(cs) + ")"; break;
  }
}*/


///////////////////////////////////////////////private//////////////////////

void VictronCharger::_readVEData() {
	  uint64_t timeOld = millis();
	  while ( VICTRON_SERIAL.available() && (timeOld + TIME_OUT_READ_CHG_SERIAL > millis()) ) {
	    _myve->rxData(VICTRON_SERIAL.read());
	    _data_count++;
	  }
	  //yield();
}

boolean VictronCharger::_isNumeric(char chStr[]) {
  unsigned int stringLength = strlen(chStr);
  if (stringLength == 0) {
    return false;
  }
  for (unsigned int i = 0; i < stringLength; ++i) {
    if (isDigit(chStr[i])) {
      continue;
    }
    if (chStr[i] == '.') {
      continue;
    }
    return false;
  }
  return true;
}
