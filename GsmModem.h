/*
 * GsmModem.h
 *
 *  Created on: 06.09.2021
 *      Author: user
 */

#ifndef GSMMODEM_H_
#define GSMMODEM_H_
#include <GSMSimSMS.h>
#define SUBSCRIBER_NR "+8888888"
class GsmModem {
public:
	GsmModem(HardwareSerial *serial, int8_t rstpin, uint32_t bdrate = 4800);
	void begin();
	void loop();
	void reset();
	virtual ~GsmModem();
	bool _newMsgArrived;
	String _message;
	String _lastSender;
	GSMSimSMS * _sms;
private:
	int8_t _rstpin;
	HardwareSerial *_serial;
	uint32_t _bdrate;
	void _initializeModem();



};

#endif /* GSMMODEM_H_ */
