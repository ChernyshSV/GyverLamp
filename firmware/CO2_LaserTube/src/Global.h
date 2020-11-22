#include <FastLED.h>
#include <Settings.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "timer2Minim.h"
#include <Arduino.h>
#include <Alarm.h>
#include <LedMode.h>
// ------------------- ТИПЫ --------------------
extern CRGB leds[NUM_LEDS];

extern WiFiUDP Udp;
extern NTPClient timeClient;

extern unsigned char matrixValue[8][16];

extern unsigned char dawnMode;
extern boolean dawnFlag;

extern boolean manualOff;


extern signed char currentMode;
extern boolean loadingFlag;
extern boolean ONflag;
extern unsigned int eepromTimer;
extern boolean settChanged;

extern const unsigned char maxDim;

extern LedMode modes[];

extern Alarm alarm[];