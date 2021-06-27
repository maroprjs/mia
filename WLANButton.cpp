/*
 * WLANButton.cpp
 *
 *  Created on: 25.06.2021
 *      Author: maro
 */

#include "WLANButton.h"

WLANButton::WLANButton(uint8_t wlanButtonPin, WLANRouter* wlanRouter, Gateway* gw) {
	_wlanButtonPin = wlanButtonPin;
	_lastButtonState = HIGH;
	_buttonState = HIGH;
	_lastDebounceTime = 0;
	_wlanRouter = wlanRouter;
	_gw = gw;
}

void WLANButton::begin(){
	pinMode(_wlanButtonPin, INPUT_PULLUP);
}

void WLANButton::loop(){
	bool reading = digitalRead(_wlanButtonPin);
	if (reading != _lastButtonState) {
	    // reset the debouncing timer
	    _lastDebounceTime = millis();
	}
	if ((millis() - _lastDebounceTime) > WLAN_BUTTON_DEBOUNCE_DELAY) {
	   // whatever the reading is at, it's been there for longer than the debounce
	   // delay, so take it as the actual current state:

	   // if the button state has changed:
	   if (reading != _buttonState) {
	      _buttonState = reading;

	      // only toggle the WLAN if the new button state is LOW
	      if (_buttonState == LOW) {
	        _wlanRouter->toggle();
	        _gw->toggle();
          }
	   }
	}
	_lastButtonState = reading;

}

WLANButton::~WLANButton() {
	// TODO Auto-generated destructor stub
}

