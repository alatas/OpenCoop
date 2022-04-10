#include "RTC.h"

RTC::RTC(Context *context, uint8_t clkPin, uint8_t ioPin, uint8_t rstPin, float latitude, float longitude, int timezone, int8_t sunrise_delay, int8_t sunset_delay) : Component(context)
{
  this->clkPin = clkPin;
  this->ioPin = ioPin;
  this->rstPin = rstPin;
  this->latitude = latitude;
  this->longitude = longitude;
  this->timezone = timezone;
  this->sunrise_delay = sunrise_delay;
  this->sunset_delay = sunset_delay;
}

void RTC::Setup()
{
  if (!threeWire)
  {
    threeWire = new ThreeWire{ioPin, clkPin, rstPin};
    rtc = new RtcDS1302<ThreeWire>{*threeWire};
  }

  timelord.TimeZone(timezone);
  timelord.Position(latitude, longitude);

  context->logger->Info(Messages::RTC_INIT);
  rtc->Begin();
  TestRTC();
}

void RTC::Loop()
{
}

void RTC::TestRTC()
{
  if (rtc->GetIsWriteProtected())
  {
    context->logger->Debug(Messages::RTC_READONLY);
    rtc->SetIsWriteProtected(false);
  }

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  if (!rtc->IsDateTimeValid())
  {
    context->logger->Debug(Messages::RTC_NO_VALID_TIME);
    rtc->SetDateTime(compiled);
  }
  else
  {
    context->logger->Debug(Messages::RTC_VALID_TIME);
  }

  if (!rtc->GetIsRunning())
  {
    context->logger->Debug(Messages::RTC_STARTING);
    rtc->SetIsRunning(true);
  }

  context->logger->Debug(Messages::RTC_TESTING);
  context->logger->Debug(Messages::RTC_COMPILATION_TIME);
  printDateTimeRaw(compiled);
  delay(100);

  RtcDateTime now = rtc->GetDateTime();
  context->logger->Debug(Messages::RTC_RTC_TIME);
  printDateTimeRaw(now);

  if (now < compiled)
  {
    context->logger->Debug(Messages::RTC_OLDER);
    rtc->SetDateTime(compiled);
  }
  else if (now >= compiled)
  {
    context->logger->Debug(Messages::RTC_NEWER);
  }

  context->logger->Debug(Messages::RTC_SUNRISE_SUNSET);
  printDateTimeRaw(getSunsetSunrise(true));
  printDateTimeRaw(getSunsetSunrise(false));
  if (IsDaytime())
  {
    context->logger->Debug(Messages::RTC_DAYTIME);
  }
  else
  {
    context->logger->Debug(Messages::RTC_NIGHTTIME);
  }
}

bool RTC::IsDaytime()
{
  RtcDateTime now = rtc->GetDateTime();
  RtcDateTime sunrise = getSunsetSunrise(true);
  RtcDateTime sunset = getSunsetSunrise(false);
  return (now >= sunrise && now < sunset);
}

uint8_t *RTC::GetRTCTime()
{
  RtcDateTime now = rtc->GetDateTime();
  return new uint8_t[2]{now.Hour(), now.Minute()};
}