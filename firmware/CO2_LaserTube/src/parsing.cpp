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
#include <effectTicker.h>

void sendCurrent();
void sendAlarms();

void parseUDP()
{
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = 0;
    inputBuffer = packetBuffer;

    if (inputBuffer.startsWith("DEB"))
    {
      if (sendSettings_flag)
        sendCurrent();
      else
        inputBuffer = "OK " + timeClient.getFormattedTime();
      sendSettings_flag = false;
    }
    else if (inputBuffer.startsWith("GET"))
    {
      sendCurrent();
    }
    else if (inputBuffer.startsWith("EFF"))
    {
      saveEEPROM();
      currentMode = (unsigned char)inputBuffer.substring(3).toInt();
      loadingFlag = true;
      FastLED.clear();
      delay(1);
      sendCurrent();
      FastLED.setBrightness(modes[currentMode].brightness);
    }
    else if (inputBuffer.startsWith("BRI"))
    {
      modes[currentMode].brightness = inputBuffer.substring(3).toInt();
      FastLED.setBrightness(modes[currentMode].brightness);
      settChanged = true;
      eepromTimer = millis();
    }
    else if (inputBuffer.startsWith("SPD"))
    {
      modes[currentMode].speed = inputBuffer.substring(3).toInt();
      loadingFlag = true;
      settChanged = true;
      eepromTimer = millis();
    }
    else if (inputBuffer.startsWith("SCA"))
    {
      modes[currentMode].scale = inputBuffer.substring(3).toInt();
      loadingFlag = true;
      settChanged = true;
      eepromTimer = millis();
    }
    else if (inputBuffer.startsWith("P_ON"))
    {
      ONflag = true;
      changePower();
      sendCurrent();
    }
    else if (inputBuffer.startsWith("P_OFF"))
    {
      ONflag = false;
      changePower();
      sendCurrent();
    }
    else if (inputBuffer.startsWith("ALM_SET"))
    {
      unsigned char alarmNum = (char)inputBuffer[7] - '0';
      alarmNum -= 1;
      if (inputBuffer.indexOf("ON") != -1)
      {
        alarm[alarmNum].state = true;
        inputBuffer = "alm #" + String(alarmNum + 1) + " ON";
      }
      else if (inputBuffer.indexOf("OFF") != -1)
      {
        alarm[alarmNum].state = false;
        inputBuffer = "alm #" + String(alarmNum + 1) + " OFF";
      }
      else
      {
        int almTime = inputBuffer.substring(8).toInt();
        alarm[alarmNum].time = almTime;
        unsigned char hour = floor(almTime / 60);
        unsigned char minute = almTime - hour * 60;
        inputBuffer = "alm #" + String(alarmNum + 1) +
                      " " + String(hour) +
                      ":" + String(minute);
      }
      saveAlarm(alarmNum);
      manualOff = false;
    }
    else if (inputBuffer.startsWith("ALM_GET"))
    {
      sendAlarms();
    }
    else if (inputBuffer.startsWith("DAWN"))
    {
      dawnMode = inputBuffer.substring(4).toInt() - 1;
      saveDawnMmode();
    }

    char reply[inputBuffer.length() + 1];
    inputBuffer.toCharArray(reply, inputBuffer.length() + 1);
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(reply);
    Udp.endPacket();
  }
}

void sendCurrent()
{
  inputBuffer = "CURR";
  inputBuffer += " ";
  inputBuffer += String(currentMode);
  inputBuffer += " ";
  inputBuffer += String(modes[currentMode].brightness);
  inputBuffer += " ";
  inputBuffer += String(modes[currentMode].speed);
  inputBuffer += " ";
  inputBuffer += String(modes[currentMode].scale);
  inputBuffer += " ";
  inputBuffer += String(ONflag);
}

void sendSettings()
{
  sendCurrent();
  char reply[inputBuffer.length() + 1];
  inputBuffer.toCharArray(reply, inputBuffer.length() + 1);
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Udp.write(reply);
  Udp.endPacket();
}

void sendAlarms()
{
  inputBuffer = "ALMS ";
  for (unsigned char i = 0; i < 7; i++)
  {
    inputBuffer += String(alarm[i].state);
    inputBuffer += " ";
  }
  for (unsigned char i = 0; i < 7; i++)
  {
    inputBuffer += String(alarm[i].time);
    inputBuffer += " ";
  }
  inputBuffer += (dawnMode + 1);
}
