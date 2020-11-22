#include <FastLED.h>
#include <Settings.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "timer2Minim.h"
#include <Global.h>
#include <runningText.h>

void SetTime();
void timeTick();
void updTime();