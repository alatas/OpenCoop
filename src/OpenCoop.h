#ifndef __OPENCOOP_H
#define __OPENCOOP_H

#include <Arduino.h>

#include <Context.h>
#include <Button.h>
#include <Motor.h>
#include <Ring.h>
#include <LCD.h>
#include <RTC.h>
#include <Logger.h>

#include <State.h>
#include <DaytimeState.h>
#include <NighttimeState.h>
#include <OpeningState.h>
#include <ClosingState.h>

class TM1637;

class OpenCoop
{
private:
  const static uint8_t upperPin = 4;
  const static uint8_t lowerPin = 5;

  const static uint8_t rtcCLKPin = 6; // CLK
  const static uint8_t rtcIOPin = 7;  // IO/DAT
  const static uint8_t rtcRSTPin = 8; // RST
  const float LONGITUDE = 33.9;
  const float LATITUDE = 39.4;
  const static int TimeZone = 3 * 60;

  const static int8_t sunrise_delay = -30;
  const static int8_t sunset_delay = 30;

  const static uint8_t driverPin1 = 9;  // IN1_A
  const static uint8_t driverPin2 = 10; // IN2_B

  const static uint8_t lcdIOPin = 11;  // DIO
  const static uint8_t lcdCLKPin = 12; // CLK
  const static uint8_t lcdBrightness = 2;

  const static uint8_t buzzerPin = 2;

public:
  Context *context{nullptr};

  OpenCoop();

  void Setup();
  void Loop();
};

#endif