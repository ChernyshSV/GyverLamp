#include <EepromExt.h>

void saveEEPROM()
{
  EEPROM.put(3 * currentMode + 40, modes[currentMode]);
  EEPROM.commit();
}

void eepromTick()
{
  if (settChanged && millis() - eepromTimer > 30000)
  {
    settChanged = false;
    eepromTimer = millis();
    saveEEPROM();
    if (EEPROM.read(200) != currentMode)
      EEPROM.write(200, currentMode);
    EEPROM.commit();
  }
}

void eeWriteInt(int pos, int val)
{
  unsigned char *p = (unsigned char *)&val;
  EEPROM.write(pos, *p);
  EEPROM.write(pos + 1, *(p + 1));
  EEPROM.write(pos + 2, *(p + 2));
  EEPROM.write(pos + 3, *(p + 3));
  EEPROM.commit();
}

int eeGetInt(int pos)
{
  int val;
  unsigned char *p = (unsigned char *)&val;
  *p = EEPROM.read(pos);
  *(p + 1) = EEPROM.read(pos + 1);
  *(p + 2) = EEPROM.read(pos + 2);
  *(p + 3) = EEPROM.read(pos + 3);
  return val;
}

void saveAlarm(unsigned char almNumber)
{
  EEPROM.write(5 * almNumber, alarm[almNumber].state); // рассвет
  eeWriteInt(5 * almNumber + 1, alarm[almNumber].time);
  EEPROM.commit();
}

void saveDawnMmode()
{
  EEPROM.write(199, dawnMode); // рассвет
  EEPROM.commit();
}
