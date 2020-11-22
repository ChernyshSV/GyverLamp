#include <Global.h>
#include <Settings.h>
#include <FastLED.h>
#include <utility.h>
#include <pgmspace.h>
#include <Arduino.h>
#include <fonts.h>
// работа с бегущим текстом

// **************** НАСТРОЙКИ ****************
#define TEXT_DIRECTION 1 // 1 - по горизонтали, 0 - по вертикали
#define MIRR_V 0         // отразить текст по вертикали (0 / 1)
#define MIRR_H 0         // отразить текст по горизонтали (0 / 1)

#define TEXT_HEIGHT 3 // высота, на которой бежит текст (от низа матрицы)
#define LET_WIDTH 5   // ширина буквы шрифта
#define LET_HEIGHT 8  // высота буквы шрифта
#define SPACE 1       // пробел

// --------------------- ДЛЯ РАЗРАБОТЧИКОВ ----------------------

int offset = WIDTH;
unsigned int scrollTimer;

unsigned char getFont(unsigned char font, unsigned char row);


void resetString()
{
  offset = WIDTH;
}

void drawLetter(unsigned char index, unsigned char letter, int16_t offset, CRGB textColor)
{
  signed char start_pos = 0, finish_pos = LET_WIDTH;

  if (offset < -LET_WIDTH || offset > WIDTH)
    return;
  if (offset < 0)
    start_pos = -offset;
  if (offset > (WIDTH - LET_WIDTH))
    finish_pos = WIDTH - offset;

  for (unsigned char i = start_pos; i < finish_pos; i++)
  {
    int thisByte;
    if (MIRR_V)
      thisByte = getFont((unsigned char)letter, LET_WIDTH - 1 - i);
    else
      thisByte = getFont((unsigned char)letter, i);

    for (unsigned char j = 0; j < LET_HEIGHT; j++)
    {
      boolean thisBit;

      if (MIRR_H)
        thisBit = thisByte & (1 << j);
      else
        thisBit = thisByte & (1 << (LET_HEIGHT - 1 - j));

      // рисуем столбец (i - горизонтальная позиция, j - вертикальная)
      if (TEXT_DIRECTION)
      {
        if (thisBit)
          leds[getPixelNumber(offset + i, TEXT_HEIGHT + j)] = textColor;
        //else drawPixelXY(offset + i, TEXT_HEIGHT + j, 0x000000);
      }
      else
      {
        if (thisBit)
          leds[getPixelNumber(i, offset + TEXT_HEIGHT + j)] = textColor;
        //else drawPixelXY(i, offset + TEXT_HEIGHT + j, 0x000000);
      }
    }
  }
}

boolean fillString(String text, CRGB textColor, boolean clear)
{
  if (loadingFlag)
  {
    offset = WIDTH; // перемотка в правый край
    loadingFlag = false;
  }

  if (millis() - scrollTimer >= 100)
  {
    scrollTimer = millis();
    if (clear)
      FastLED.clear();
    unsigned char i = 0, j = 0;
    while (text[i] != '\0')
    {
      if ((unsigned char)text[i] > 191)
      { // работаем с русскими буквами!
        i++;
      }
      else
      {
        drawLetter(j, text[i], offset + j * (LET_WIDTH + SPACE), textColor);
        i++;
        j++;
      }
    }

    offset--;
    if (offset < -j * (LET_WIDTH + SPACE))
    { // строка убежала
      offset = WIDTH + 3;
      return true;
    }
    FastLED.show();
  }
  return false;
}



// ------------- СЛУЖЕБНЫЕ ФУНКЦИИ --------------

// интерпретатор кода символа в массиве fontHEX (для Arduino IDE 1.8.* и выше)
unsigned char getFont(unsigned char font, unsigned char row)
{
  font = font - '0' + 16; // перевод код символа из таблицы ASCII в номер согласно нумерации массива
  if (font <= 90)
    return pgm_read_byte(&(fontHEX[font][row])); // для английских букв и символов
  else if (font >= 112 && font <= 159)
  { // и пизд*ц ждя русских
    return pgm_read_byte(&(fontHEX[font - 17][row]));
  }
  else if (font >= 96 && font <= 111)
  {
    return pgm_read_byte(&(fontHEX[font + 47][row]));
  }
  
  return 0;
}
