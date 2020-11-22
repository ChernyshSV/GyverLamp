#ifndef ALARM_H
#define ALARM_H
#include <Arduino.h>
struct Alarm
{
    boolean state = false;
    int time = 0;
};

#endif