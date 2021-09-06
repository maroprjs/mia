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
#include "GsmModem.h"
#include "GsmModem.h"
#include "MiaUI.h"
#include "Eltako.h"
#include "VictronCharger.h"


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

/*************************************************************
 * GSM Modem
 */
//#define MODEM_SERIAL 	Serial3
//#define MODEM_RST	6
#define MODEM_SERIAL 	Serial4
#define MODEM_RST	30
GsmModem gsm(&MODEM_SERIAL,MODEM_RST);

/*************************************************************
 * Eltako Latchin Relais for appliances (Main Power Supply for Lights and Sockets)
 */
#define ELTAKO_PIN 17
#define PROBE_PIN A9 //to check if eltako is on
Eltako eltako(ELTAKO_PIN, PROBE_PIN);

/*************************************************************
 * VictronCharger
 */
VictronCharger charger;

/*************************************************************
 * user interface via sms or serial
 */
MiaUI miaUI(&gsm, &gw, &wlanRouter, &eltako ,&charger);

void setup()
{
	Serial.begin(9600);
	gsm.begin();
	GATEWAY_SERIAL.begin(9600);
	wlanPwr.begin();
	gwPwr.begin();
	wlanButton.begin();
	wlanRouter.begin();
	gw.begin();
    eltako.begin();
	charger.begin();
	miaUI.begin();

}

// The loop function is called in an endless loop
void loop()
{
	gsm.loop();//checks for incomming events -> SMSs
	wlanPwr.loop();
	gwPwr.loop();
	wlanButton.loop();
	wlanRouter.loop();
	gw.loop();
    eltako.loop();
	charger.loop();
	miaUI.loop();

}
