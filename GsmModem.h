/*
 * GsmModem.h
 *
 *  Created on: 06.09.2021
 *      Author: user
 */

#ifndef GSMMODEM_H_
#define GSMMODEM_H_
#include <GSMSimSMS.h>

class GsmModem {
public:
	GsmModem(HardwareSerial *serial, int8_t rstpin, uint32_t bdrate = 4800);
	void begin();
	void loop();
	virtual ~GsmModem();
private:
	int8_t _rstpin;
	HardwareSerial *_serial;
	uint32_t _bdrate;
	GSMSimSMS * _sms;
};

#endif /* GSMMODEM_H_ */
