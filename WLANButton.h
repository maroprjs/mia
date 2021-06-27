/*
 * WLANButton.h
 *
 *  Created on: 25.06.2021
 *      Author: maro
 */

#ifndef WLANBUTTON_H_
#define WLANBUTTON_H_
#include "Arduino.h"
#include "WLANRouter.h"
#include "Gateway.h"

#define WLAN_BUTTON_DEBOUNCE_DELAY  50 //ms

class WLANButton {
public:
	WLANButton(uint8_t wlanButtonPin, WLANRouter* wlanRouter, Gateway* gw);
	void begin();
	void loop();
	virtual ~WLANButton();
private:
	uint8_t _wlanButtonPin;
	bool _lastButtonState;
	bool _buttonState;             // the current reading from the input pin
	uint32_t _lastDebounceTime;
	WLANRouter* _wlanRouter;
	Gateway* _gw;
};

#endif /* WLANBUTTON_H_ */
