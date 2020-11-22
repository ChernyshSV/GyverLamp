#include <Global.h>
#include <FastLED.h>
#include <utility.h>
#include <pgmspace.h>
#include <Arduino.h>
#include <fonts.h>

void drawLetter(unsigned char, unsigned char, int16_t, CRGB);
boolean fillString(String, CRGB, boolean);
void resetString();