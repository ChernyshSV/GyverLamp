#include "EEPROM.h"
#include <Global.h>

int eeGetInt(int);
void eeWriteInt(int, int);
void saveEEPROM();
void saveAlarm(unsigned char almNumber);
void saveDawnMmode();
void eepromTick();