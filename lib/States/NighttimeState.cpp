#include "NighttimeState.h"

void NighttimeState::Loop()
{
  if (context->rtc->IsDaytime())
  {
    context->logger->Info(Messages::SW_DAYTIME_STATE);
    context->TransitionTo(context->daytimeState);
  }
  else if (!context->lower->IsPressed())
  {
    context->logger->Info(Messages::SW_CLOSING_STATE);
    context->TransitionTo(context->closingState);
  }
  else
  {
    context->lcd->TurnOff();
    delay(500);
  }
}

void NighttimeState::Setup()
{
}