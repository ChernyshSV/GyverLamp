/*
  Скетч к проекту "Многофункциональный RGB светильник"
  Страница проекта (схемы, описания): https://alexgyver.ru/GyverLamp/
  Исходники на GitHub: https://github.com/AlexGyver/GyverLamp/
  Нравится, как написан код? Поддержи автора! https://alexgyver.ru/support_alex/
  Автор: AlexGyver, AlexGyver Technologies, 2019
  https://AlexGyver.ru/
*/

/*
  Версия 1.5.1
  - Оптимизировано обращение к серверу времени (нет подвисаний при отсутствии интернета)
  - Оптимизация под пины NodeMCU

  Версия 1.5.2
  - Исправлен незначительный баг с таймером
  - Исправлено падение по WDT при выводе IP
  - Исправлен баг с переназначением времени будильника
  - Исправлено переключение с первого на последний режимы
  - Приложение автоматически получает настройки с кнопки
  - Бегущая строка с текущим временем во время рассвета

  Версия 1.5.3
  - Увеличена плавность рассвета
  - Поправлен баг с отображением времени рассвета

  Версия 1.5.4
  - Поправлены глюки во время рассвета
  
  Версия 1.5.5
  - Поправлено невыключение света во время рассвета

*/

// Ссылка для менеджера плат:
// http://arduino.esp8266.com/stable/package_esp8266com_index.json

// Для WEMOS выбираем плату LOLIN(WEMOS) D1 R2 & mini
// Для NodeMCU выбираем NodeMCU 1.0 (ESP-12E Module)

#include "timer2Minim.h"
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <EEPROM.h>
#include <NTPClient.h>
//#include <GyverButton.h>
#include "fonts.h"
#include <Settings.h>
#include <Global.h>

#include <EepromExt.h>
#include <parsing.h>
#include <time.h>
//GButton touch(BTN_PIN, LOW_PULL, NORM_OPEN);

void setup()
{
  ESP.wdtDisable();
  //ESP.wdtEnable(WDTO_8S);
  Serial.begin(9600);
  // ЛЕНТА
  FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS) /*.setCorrection( TypicalLEDStrip )*/;
  FastLED.setBrightness(BRIGHTNESS);
  if (CURRENT_LIMIT > 0)
    FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
  FastLED.show();

  //touch.setStepTimeout(100);
  //touch.setClickTimeout(500);

  Serial.begin(115200);
  Serial.println();
  delay(1000);

  // WI-FI
  if (ESP_MODE == 0)
  { // режим точки доступа
    WiFi.softAPConfig(IPAddress(IP_AP[0], IP_AP[1], IP_AP[2], IP_AP[3]),
                      IPAddress(192, 168, 4, 1),
                      IPAddress(255, 255, 255, 0));

    WiFi.softAP(AP_NameChar, WiFiPassword);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("Access point Mode");
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    server.begin();
  }
  else
  { // подключаемся к роутеру
    Serial.print("WiFi manager");
    WiFiManager wifiManager;
    wifiManager.setDebugOutput(false);

#if (USE_BUTTON == 1)
    if (digitalRead(BTN_PIN))
      wifiManager.resetSettings();
#endif

    wifiManager.autoConnect(autoConnectSSID, autoConnectPass);
    /*WiFi.config(IPAddress(IP_STA[0], IP_STA[1], IP_STA[2], IP_STA[3]),
                IPAddress(192, 168, 1, 1),
                IPAddress(255, 255, 255, 0));*/
    Serial.print("Connected! IP address: ");
    Serial.println(WiFi.localIP());
    lampIP = WiFi.localIP().toString();
  }
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);

  // EEPROM
  EEPROM.begin(202);
  delay(50);
  if (EEPROM.read(198) != 20)
  { // первый запуск
    EEPROM.write(198, 20);
    EEPROM.commit();

    for (unsigned char i = 0; i < MODE_AMOUNT; i++)
    {
      EEPROM.put(3 * i + 40, modes[i]);
      EEPROM.commit();
    }
    for (unsigned char i = 0; i < 7; i++)
    {
      EEPROM.write(5 * i, alarm[i].state); // рассвет
      eeWriteInt(5 * i + 1, alarm[i].time);
      EEPROM.commit();
    }
    EEPROM.write(199, 0); // рассвет
    EEPROM.write(200, 0); // режим
    EEPROM.commit();
  }
  for (unsigned char i = 0; i < MODE_AMOUNT; i++)
  {
    EEPROM.get(3 * i + 40, modes[i]);
  }
  for (unsigned char i = 0; i < 7; i++)
  {
    alarm[i].state = EEPROM.read(5 * i);
    alarm[i].time = eeGetInt(5 * i + 1);
  }
  dawnMode = EEPROM.read(199);
  currentMode = (signed char)EEPROM.read(200);

  // отправляем настройки
  sendSettings();

  timeClient.begin();
  memset(matrixValue, 0, sizeof(matrixValue));

  randomSeed(micros());

  // получаем время
  unsigned char count = 0;
  while (count < 5)
  {
    if (timeClient.update())
    {
      hrs = timeClient.getHours();
      mins = timeClient.getMinutes();
      secs = timeClient.getSeconds();
      days = timeClient.getDay();
      break;
    }
    count++;
    delay(500);
  }
  updTime();
}

void loop()
{
  parseUDP();
  effectsTick();
  eepromTick();
  timeTick();
#if (USE_BUTTON == 1)
  buttonTick();
#endif
  ESP.wdtFeed(); // пнуть собаку
  yield();       // ещё раз пнуть собаку
}
