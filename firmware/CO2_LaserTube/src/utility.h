#include <FastLED.h>
#include <Global.h>

unsigned int getPixColorXY(signed char x, signed char y);
unsigned int getPixColor(int thisSegm);
uint16_t getPixelNumber(signed char x, signed char y);
void drawPixelXY(signed char x, signed char y, CRGB color);