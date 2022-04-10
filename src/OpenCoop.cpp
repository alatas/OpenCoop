#include <OpenCoop.h>

OpenCoop::OpenCoop()
{
}

void OpenCoop::Setup()
{
  context = new Context{};

  context->logger = new Logger{};
  context->logger->Setup();

  context->upper = new Button{context, "Upper", upperPin};
  context->AddComponent(context->upper);

  context->lower = new Button{context, "Lower", lowerPin};
  context->AddComponent(context->lower);

  context->lcd = new LCD{context, lcdCLKPin, lcdIOPin, lcdBrightness};
  context->AddComponent(context->lcd);

  context->motor = new Motor{context, driverPin1, driverPin2};
  context->AddComponent(context->motor);

  context->ring = new Ring{context, buzzerPin};
  context->AddComponent(context->ring);

  context->rtc = new RTC{context, rtcCLKPin, rtcIOPin, rtcRSTPin, LATITUDE, LONGITUDE, TimeZone, sunrise_delay, sunset_delay};
  context->AddComponent(context->rtc);

  context->Setup();

  context->daytimeState = (State *)new DaytimeState{context};
  context->nighttimeState = (State *)new NighttimeState{context};
  context->openingState = (State *)new OpeningState{context};
  context->closingState = (State *)new ClosingState{context};

  if (context->rtc->IsDaytime())
  {
    context->logger->Info(Messages::SW_DAYTIME_STATE);
    context->TransitionTo(context->daytimeState);
  }
  else
  {
    context->logger->Info(Messages::SW_NIGHTTIME_STATE);
    context->TransitionTo(context->nighttimeState);
  }
}

void OpenCoop::Loop()
{
  context->Loop();
}