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
	_newMsgArrived = false;
	_message = "";
	_lastSender = SUBSCRIBER_NUMBER;

}

void GsmModem::begin(){
	_serial->begin(_bdrate);
	delay(1000);
	_initializeModem();


}
void GsmModem::loop(){
	if(_serial->available()) {
	      String buffer = "";
	      buffer = _serial->readString();

	      /**/
	      // This example for how you catch incoming calls.
	      //Serial.print("buf: ");
	      //Serial.println(buffer);
	      if(buffer.indexOf("+CMTI:") != -1) {

	        Serial.print("SMS Index No... ");
	        int indexno = _sms->indexFromSerial(buffer);
	        Serial.println(indexno);

	        Serial.print("Who send the message?...");
          _lastSender = _sms->getSenderNo(indexno);
          Serial.println(_lastSender);

          Serial.print("Read the message... ");
          //String teststr = _sms->readFromSerial(buffer);
          _message = _sms->readFromSerial(buffer);
          //Serial.println(teststr);
          _message = _message.substring(_message.indexOf("MESSAGE:")+8);
          Serial.println(_message);

	        //_sms->deleteAll();
	        //Serial.print("SMS to any number... ");
	        //Serial.println(_sms->send(sender.c_str(), "Selam kardesim, naber?"));
	        _newMsgArrived = true;
	      } else {
	        //Serial.println(buffer);
	      }

	  }
}

void GsmModem::reset(){
    Serial.println("resetting modem!");
    pinMode(_rstpin, OUTPUT);
    digitalWrite(_rstpin, HIGH);
    delay(10);
    digitalWrite(_rstpin, LOW);
    delay(100);
    digitalWrite(_rstpin, HIGH);
    delay(10000);
    _initializeModem();
    _sms->send(SUBSCRIBER_NUMBER, "modem reseted!");

}

GsmModem::~GsmModem() {
	// TODO Auto-generated destructor stub
}

void GsmModem::_initializeModem(){
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
