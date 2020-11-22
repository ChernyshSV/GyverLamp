#ifndef TIMER2MINIM_H
#define TIMER2MINIM_H

#include <FastLED.h>
#include <Arduino.h>


// мини-класс таймера, версия 2.0
// использован улучшенный алгоритм таймера на millis
// алгоритм чуть медленнее, но обеспечивает кратные интервалы и защиту от пропусков и переполнений

class timerMinim
{
public:
  timerMinim(unsigned int interval)
  {
    _interval = interval;
    _timer = millis();
  }                                       // объявление таймера с указанием интервала
  void setInterval(unsigned int interval) // установка интервала работы таймера
  {
    _interval = (interval == 0) ? 1 : interval; // защита от ввода 0
  }
  boolean isReady() // возвращает true, когда пришло время. Сбрасывается в false сам (AUTO) или вручную (MANUAL)
  {
    unsigned int thisMls = millis();
    if (thisMls - _timer >= _interval)
    {
      do
      {
        _timer += _interval;
        if (_timer < _interval)
          break;                              // переполнение unsigned int
      } while (_timer < thisMls - _interval); // защита от пропуска шага
      return true;
    }
    else
    {
      return false;
    }
  }

  void reset() // ручной сброс таймера на установленный интервал
  {
    _timer = millis();
  }

private:
  unsigned int _timer = 0;
  unsigned int _interval = 0;
};
#endif