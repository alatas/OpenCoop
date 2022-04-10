#ifndef __RTC_H
#define __RTC_H

#include <Arduino.h>
#include <Component.h>
#include <Context.h>
#include <Logger.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <TimeLord.h>

class RTC : public Component
{

private:
  uint8_t clkPin;
  uint8_t ioPin;
  uint8_t rstPin;

  int8_t sunrise_delay;
  int8_t sunset_delay;

  float latitude;
  float longitude;
  int timezone;

  TimeLord timelord;

  ThreeWire *threeWire{nullptr};
  RtcDS1302<ThreeWire> *rtc{nullptr};

  char chars[25];

  String convertTime2String(RtcDateTime datetime, char *format = (char *)"%02d:%02d")
  {
    sprintf(chars, format, datetime.Hour(), datetime.Minute());
    String str(chars);
    str.trim();
    return str;
  }

  String convertDate2String(RtcDateTime datetime, char *format = (char *)"%d-%02d-%02d")
  {
    sprintf(chars, format, datetime.Year(), datetime.Month(), datetime.Day());
    String str(chars);
    str.trim();
    return str;
  }

  void printDateTimeRaw(RtcDateTime datetime)
  {
    char buffer[20];
    sprintf(buffer, "%d-%02d-%02d %02d:%02d:%02d", datetime.Year(), datetime.Month(), datetime.Day(), datetime.Hour(), datetime.Minute(), datetime.Second());
    context->logger->Raw(buffer);
  }

  RtcDateTime getSunsetSunrise(bool sunrise = true)
  {
    RtcDateTime now = rtc->GetDateTime();
    byte today[] = {0,
                    0,
                    12,
                    now.Day(),
                    now.Month(),
                    byte(now.Year() - 2000)};

    if (sunrise)
      timelord.SunRise(today);
    else
      timelord.SunSet(today);

    RtcDateTime real = RtcDateTime(today[tl_year] + 2000, today[tl_month], today[tl_day], today[tl_hour], today[tl_minute], today[tl_second]);

    if (sunrise)
      return RtcDateTime(real.TotalSeconds() + (sunrise_delay * 60));
    else
      return RtcDateTime(real.TotalSeconds() + (sunset_delay * 60));
  }

public:
  RTC(Context *context, uint8_t clkPin, uint8_t ioPin, uint8_t rstPin, float latitude, float longitude, int timezone, int8_t sunrise_delay, int8_t sunset_delay);

  void Setup() override;
  void Loop() override;

  void TestRTC();
  String GetTime(char *format);
  uint8_t *GetRTCTime();

  bool IsDaytime();
};
#endif