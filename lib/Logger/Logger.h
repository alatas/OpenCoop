#ifndef __LOGGER_H
#define __LOGGER_H

#include "Arduino.h"

enum class VerboseLevels : int
{
  DEBUG,
  INFO,
  WARN,
  ERROR
};

enum class Messages
{
  SW_NIGHTTIME_STATE,
  SW_DAYTIME_STATE,
  SW_OPENING_STATE,
  SW_CLOSING_STATE,
  SW_CLOSING_DOOR,
  SW_CLOSING_STOP,
  SW_OPENING_DOOR,
  SW_OPENING_STOP,
  LCD_INIT,
  LCD_DISP_SEG,
  LCD_DISP_CLEAR,
  LCD_DISP_TIME,
  LCD_DISP_OPENING,
  LCD_DISP_CLOSING,
  BUTTON_INIT,
  LED_INIT,
  LED_ON,
  LED_OFF,
  MOTOR_INIT,
  MOTOR_FORWARD,
  MOTOR_BACKWARD,
  MOTOR_STOPPED,
  RING_INIT,
  RING_STARTED,
  RING_STOPPED,
  RING_BEEP,
  RTC_INIT,
  RTC_READONLY,
  RTC_NO_VALID_TIME,
  RTC_VALID_TIME,
  RTC_STARTING,
  RTC_OLDER,
  RTC_NEWER,
  RTC_TESTING,
  RTC_DAYTIME,
  RTC_NIGHTTIME,
  RTC_COMPILATION_TIME,
  RTC_RTC_TIME,
  RTC_SUNRISE_SUNSET
};

class Logger
{

public:
  Logger();
  Logger(VerboseLevels _verboseLevel);

  void Setup();
  void Raw(char *str);
  void Debug(Messages msg);
  void Info(Messages msg);
  void Warn(Messages msg);
  void Error(Messages msg);

private:
  VerboseLevels verboseLevel;

  char *verboseLevels[4] =
      {
          (char *)"DEBUG",
          (char *)"INFO",
          (char *)"WARN",
          (char *)"ERROR"};

  char *messages[50] = {
      (char *)"Switching to nighttime state", // 0
      (char *)"Switching to daytime state",   // 1
      (char *)"Switching to opening state",   // 2
      (char *)"Switching to closing state",   // 3
      (char *)"Starting to close the door",   //...
      (char *)"Door is closed, stopping",
      (char *)"Starting to open the door",
      (char *)"Door is openned, stopping",
      (char *)"LCD Init",
      (char *)"LCD drawing defined segments",
      (char *)"LCD Display Clear",
      (char *)"LCD Display Time",
      (char *)"LCD Display Opening",
      (char *)"LCD Display Closing",
      (char *)"Button Init",
      (char *)"LED Init",
      (char *)"LED On",
      (char *)"LED Off",
      (char *)"Motor Init",
      (char *)"Motor Going Forward",
      (char *)"Motor Going Backward",
      (char *)"Motor Stopped",
      (char *)"Ring Init",
      (char *)"Ring Started",
      (char *)"Ring Stopped",
      (char *)"Ring Beep",
      (char *)"RTC Init",
      (char *)"RTC is write protected, removing protection",
      (char *)"RTC has no valid time, setting time",
      (char *)"RTC has valid time",
      (char *)"RTC is not running, starting",
      (char *)"RTC is older than compile time, updating",
      (char *)"RTC is newer than compile time. (this is completely normal)",
      (char *)"Testing RTC",
      (char *)"Now is daytime",
      (char *)"Now is nighttime",
      (char *)"Compilation Time:",
      (char *)"RTC Time:",
      (char *)"Sunrise and Sunset Times:",
  };

  void PrintMessage(VerboseLevels level, Messages msg)
  {

    int level_ = (int)level;
    int msg_ = (int)msg;
    Serial.flush();
    Serial.availableForWrite();
    Serial.print("[");
    Serial.print(verboseLevels[level_]);
    Serial.print("] ");
    Serial.print(messages[msg_]);
    Serial.println();
  }
};
#endif