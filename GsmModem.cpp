/*
 * GsmModem.cpp
 *
 *  Created on: 06.09.2021
 *      Author: user
 */

#include "GsmModem.h"

GsmModem::GsmModem(HardwareSerial *serial, int8_t rstpin, uint32_t bdrate ) {
	_sms = new GSMSimSMS(*serial, rstpin);
	_serial = serial;
	_rstpin = rstpin;
	_bdrate = bdrate;

}

void GsmModem::begin(){
	_serial->begin(_bdrate);
	delay(1000);
	_sms->init();
	  Serial.print("Set Phone Function... ");
	  Serial.println(_sms->setPhoneFunc(1));
	  delay(1000);

	  Serial.print("is Module Registered to Network?... ");
	  Serial.println(_sms->isRegistered());
	  delay(1000);

	  Serial.print("Signal Quality... ");
	  Serial.println(_sms->signalQuality());
	  delay(1000);

	  Serial.print("Operator Name... ");
	  Serial.println(_sms->operatorNameFromSim());
	  delay(1000);



	  Serial.print("Init SMS... ");
	  Serial.println(_sms->initSMS()); // Its optional but highly recommended. Some function work with this function.
	  delay(1000);

	  Serial.print("List Unread SMS... ");
	  Serial.println(_sms->list(true)); // Its optional but highly recommended. Some function work with this function.
	  delay(1000);


}
void GsmModem::loop(){
	if(_serial->available()) {
	      String buffer = "";
	      buffer = _serial->readString();

	      /**/
	      // This example for how you catch incoming calls.
	      Serial.print("buf: ");
	      Serial.println(buffer);
	      if(buffer.indexOf("+CMTI:") != -1) {

	        Serial.print("SMS Index No... ");
	        int indexno = _sms->indexFromSerial(buffer);
	        Serial.println(indexno);

	        Serial.print("Who send the message?...");
	        Serial.println(_sms->getSenderNo(indexno));

	        Serial.print("Read the message... ");
	        Serial.println(_sms->readFromSerial(buffer));
	        _sms->deleteAll();
	      } else {
	        Serial.println(buffer);
	      }

	  }
}

GsmModem::~GsmModem() {
	// TODO Auto-generated destructor stub
}

