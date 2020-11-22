#include <Global.h>
// ------------------- ТИПЫ --------------------
CRGB leds[NUM_LEDS];

WiFiUDP Udp;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, GMT * 3600, NTP_INTERVAL);

unsigned char matrixValue[8][16];

unsigned char dawnMode;
boolean dawnFlag = false;

boolean manualOff = false;


signed char currentMode = 0;
boolean loadingFlag = true;
boolean ONflag = true;
unsigned int eepromTimer;
boolean settChanged = false;
// Конфетти, Огонь, Радуга верт., Радуга гориз., Смена цвета,
// Безумие 3D, Облака 3D, Лава 3D, Плазма 3D, Радуга 3D,
// Павлин 3D, Зебра 3D, Лес 3D, Океан 3D,


const unsigned char maxDim = max(WIDTH, HEIGHT);

LedMode modes[MODE_AMOUNT];

Alarm alarm[7];