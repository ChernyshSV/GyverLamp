#include "timer2Minim.h"
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <EEPROM.h>
#include <NTPClient.h>
//#include <GyverButton.h>
#include "fonts.h"
#include <Settings.h>
#include <Global.h>
#include <EepromExt.h>
#include <effectTicker.h>

void parseUDP();
void sendSettings();