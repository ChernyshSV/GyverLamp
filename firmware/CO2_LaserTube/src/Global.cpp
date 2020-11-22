#include <Global.h>
// ------------------- ТИПЫ --------------------
CRGB leds[NUM_LEDS];
WiFiServer server(80);
WiFiUDP Udp;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, GMT * 3600, NTP_INTERVAL);
timerMinim timeTimer(1000);
timerMinim timeStrTimer(120);

unsigned char hrs, mins, secs;
unsigned char days;
unsigned char matrixValue[8][16];
String lampIP = "";

String timeStr = "00:00";

const unsigned char dawnOffsets[] = {5, 10, 15, 20, 25, 30, 40, 50, 60};
unsigned char dawnMode;
boolean dawnFlag = false;
float thisTime;
boolean manualOff = false;
boolean sendSettings_flag = false;

signed char currentMode = 0;
boolean loadingFlag = true;
boolean ONflag = true;
unsigned int eepromTimer;
boolean settChanged = false;
// Конфетти, Огонь, Радуга верт., Радуга гориз., Смена цвета,
// Безумие 3D, Облака 3D, Лава 3D, Плазма 3D, Радуга 3D,
// Павлин 3D, Зебра 3D, Лес 3D, Океан 3D,

unsigned char IP_AP[] = {192, 168, 4, 66};   // статический IP точки доступа (менять только последнюю цифру)

// ----------------- ПЕРЕМЕННЫЕ ------------------
const char *autoConnectSSID = AC_SSID;
const char *autoConnectPass = AC_PASS;
const char AP_NameChar[] = AP_SSID;
const char WiFiPassword[] = AP_PASS;
unsigned int localPort = AP_PORT;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet
String inputBuffer;
const unsigned char maxDim = max(WIDTH, HEIGHT);

LedMode modes[MODE_AMOUNT];

Alarm alarm[7];