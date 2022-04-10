#include "DaytimeState.h"

void DaytimeState::Loop()
{
  if (!context->rtc->IsDaytime())
  {
    context->logger->Info(Messages::SW_NIGHTTIME_STATE);
    context->TransitionTo(context->nighttimeState);
  }
  else if (!context->upper->IsPressed())
  {
    context->logger->Info(Messages::SW_OPENING_STATE);
    context->TransitionTo(context->openingState);
  }
  else
  {
    uint8_t *time = context->rtc->GetRTCTime();
    context->lcd->DisplayTime(*(time), *(time + 1));
    delay(500);
  }
}

void DaytimeState::Setup()
{
}