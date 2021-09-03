/*
 * MiaUI.h
 *
 *  Created on: 02.09.2021
 *      Author: user
 */

#ifndef MIAUI_H_
#define MIAUI_H_
#include "Gateway.h"
#include "WLANRouter.h"
#include "GsmModem.h"
#include "Eltako.h"
#include "VictronCharger.h"


#define SUBSCRIBER_NUMBER "+888888888888"
#define FIVE_MINUTES 300000
#define THREE_DAYS 216000000
#define PUBLISH_INTERVAL 1000


class MiaUI {
public:
	MiaUI(GsmModem *modem, Gateway *gw, WLANRouter *wlanRouter, Eltako * eltako, VictronCharger* charger);
	void begin();
	void loop();
	bool mmi(String cmd);
	virtual ~MiaUI();

private:
	void _publishDeltas();

private:
	Gateway *_gw;
	WLANRouter *_wlanRouter;
	GsmModem *_gsm;
	uint32_t _lastCall;
	Eltako* _eltako;
	VictronCharger* _charger;
	String _chargerRawDataPublished;
	String _chargerRawDataCurrent;
	uint32_t _lastPublished;
};

#endif /* MIAUI_H_ */
