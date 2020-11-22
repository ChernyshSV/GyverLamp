#include <FastLED.h>
#include <Settings.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "timer2Minim.h"
#include <Arduino.h>
#include <Alarm.h>
#include <LedMode.h>
// ------------------- ТИПЫ --------------------
extern CRGB leds[NUM_LEDS];
extern WiFiServer server;
extern WiFiUDP Udp;
extern WiFiUDP ntpUDP;
extern NTPClient timeClient;
extern timerMinim timeTimer;
extern timerMinim timeStrTimer;

extern unsigned char hrs, mins, secs;
extern unsigned char days;
extern unsigned char matrixValue[8][16];
extern String lampIP;

extern String timeStr;

extern const unsigned char dawnOffsets[];
extern unsigned char dawnMode;
extern boolean dawnFlag;
extern float thisTime;
extern boolean manualOff;
extern boolean sendSettings_flag;

extern signed char currentMode;
extern boolean loadingFlag;
extern boolean ONflag;
extern unsigned int eepromTimer;
extern boolean settChanged;
// Конфетти, Огонь, Радуга верт., Радуга гориз., Смена цвета,
// Безумие 3D, Облака 3D, Лава 3D, Плазма 3D, Радуга 3D,
// Павлин 3D, Зебра 3D, Лес 3D, Океан 3D,

extern unsigned char IP_AP[];   // статический IP точки доступа (менять только последнюю цифру)

// ----------------- ПЕРЕМЕННЫЕ ------------------
extern const char *autoConnectSSID;
extern const char *autoConnectPass;
extern const char AP_NameChar[];
extern const char WiFiPassword[];
extern unsigned int localPort;
extern char packetBuffer[]; //buffer to hold incoming packet
extern String inputBuffer;
extern const unsigned char maxDim;

struct LedMode;

extern LedMode modes[];


extern Alarm alarm[];