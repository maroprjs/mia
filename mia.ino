/**
 *  mia.ino
 *
 *
 *
 */

/////////// Includes /////////////////
#include "Arduino.h"
#include "LatchingRelay.h"
#include "WLANButton.h"
#include "Gateway.h"
#include "WLANRouter.h"


////////// Object Instantiation //////////////////
/*************************************************************
 * bi-stable Relay for WLAN Power
 *
 */
#define WLAN_RELAIS_SET_PIN 21
#define WLAN_RELAIS_RESET_PIN 20
LatchingRelay wlanPwr(WLAN_RELAIS_SET_PIN, WLAN_RELAIS_RESET_PIN);

/*************************************************************
 * bi-stable Relay for Gateway Power
 */
#define GW_RELAIS_SET_PIN 16
#define GW_RELAIS_RESET_PIN 15
LatchingRelay gwPwr(GW_RELAIS_SET_PIN, GW_RELAIS_RESET_PIN);

/*************************************************************
 * WLAN Router
 */
WLANRouter wlanRouter(&wlanPwr);

/*************************************************************
 * Gateway
 */
Gateway gw(&gwPwr);


/*************************************************************
 * Button to turn on WLAN Power
 */
#define WLAN_BUTTON_PIN 22
WLANButton wlanButton(WLAN_BUTTON_PIN, &wlanRouter, &gw);



void setup()
{
	Serial.begin(9600);
	Serial5.begin(9600);
	wlanPwr.begin();
	gwPwr.begin();
	wlanButton.begin();
	wlanRouter.begin();
	gw.begin();

}

// The loop function is called in an endless loop
void loop()
{
	wlanPwr.loop();
	gwPwr.loop();
	wlanButton.loop();
	wlanRouter.loop();
	gw.loop();
}
