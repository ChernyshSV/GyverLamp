#include <FastLED.h>
#include <Settings.h>
#include <Global.h>
// служебные функции
uint16_t getPixelNumber(signed char, signed char);
// залить все
void fillAll(CRGB color)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = color;
  }
}

// функция отрисовки точки по координатам X Y
void drawPixelXY(signed char x, signed char y, CRGB color)
{
  if (x < 0 || x > WIDTH - 1 || y < 0 || y > HEIGHT - 1)
    return;
  int thisPixel = getPixelNumber(x, y) * SEGMENTS;
  for (unsigned char i = 0; i < SEGMENTS; i++)
  {
    leds[thisPixel + i] = color;
  }
}

// функция получения цвета пикселя по его номеру
unsigned int getPixColor(int thisSegm)
{
  int thisPixel = thisSegm * SEGMENTS;
  if (thisPixel < 0 || thisPixel > NUM_LEDS - 1)
    return 0;
  return (((unsigned int)leds[thisPixel].r << 16) | ((long)leds[thisPixel].g << 8) | (long)leds[thisPixel].b);
}

// функция получения цвета пикселя в матрице по его координатам
unsigned int getPixColorXY(signed char x, signed char y)
{
  return getPixColor(getPixelNumber(x, y));
}

// **************** НАСТРОЙКА МАТРИЦЫ ****************
#if (CONNECTION_ANGLE == 0 && STRIP_DIRECTION == 0)
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y y

#elif (CONNECTION_ANGLE == 0 && STRIP_DIRECTION == 1)
#define _WIDTH HEIGHT
#define THIS_X y
#define THIS_Y x

#elif (CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 0)
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y (HEIGHT - y - 1)

#elif (CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 3)
#define _WIDTH HEIGHT
#define THIS_X (HEIGHT - y - 1)
#define THIS_Y x

#elif (CONNECTION_ANGLE == 2 && STRIP_DIRECTION == 2)
#define _WIDTH WIDTH
#define THIS_X (WIDTH - x - 1)
#define THIS_Y (HEIGHT - y - 1)

#elif (CONNECTION_ANGLE == 2 && STRIP_DIRECTION == 3)
#define _WIDTH HEIGHT
#define THIS_X (HEIGHT - y - 1)
#define THIS_Y (WIDTH - x - 1)

#elif (CONNECTION_ANGLE == 3 && STRIP_DIRECTION == 2)
#define _WIDTH WIDTH
#define THIS_X (WIDTH - x - 1)
#define THIS_Y y

#elif (CONNECTION_ANGLE == 3 && STRIP_DIRECTION == 1)
#define _WIDTH HEIGHT
#define THIS_X y
#define THIS_Y (WIDTH - x - 1)

#else
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y y
#pragma message "Wrong matrix parameters! Set to default"

#endif

// получить номер пикселя в ленте по координатам
uint16_t getPixelNumber(signed char x, signed char y)
{
  if ((THIS_Y % 2 == 0) || MATRIX_TYPE)
  { // если чётная строка
    return (THIS_Y * _WIDTH + THIS_X);
  }
  else
  { // если нечётная строка
    return (THIS_Y * _WIDTH + _WIDTH - THIS_X - 1);
  }
}
