#include "ClosingState.h"

void ClosingState::Loop()
{
  bool isDaytime = context->rtc->IsDaytime();

  if (!closing && !isDaytime && !context->lower->IsPressed())
  {
    // not closing, night and door is not closed - 0 0 0
    Start();
  }
  else if ((!closing && !isDaytime && context->lower->IsPressed()))
  {
    // not closing, nighttime, door is closed - 0 0 1
    context->logger->Info(Messages::SW_NIGHTTIME_STATE);
    context->TransitionTo(context->nighttimeState);
  }
  else if (!closing && isDaytime)
  {
    // not closing, daytime - 0 1 0 / 0 1 1
    context->logger->Info(Messages::SW_DAYTIME_STATE);
    context->TransitionTo(context->daytimeState);
  }
  else if (closing && !isDaytime && !context->lower->IsPressed())
  {
    // closing, and night and door is not closed - 1 0 0
    // wait
    if (!context->motor->IsMoving())
    {
      // timeout
      Stop();
    }
  }
  else if (closing && !isDaytime && context->lower->IsPressed())
  {
    // closing, and night and door is closed - 1 0 1
    Stop();
  }
  else if (closing && context->rtc->IsDaytime())
  {
    // closing and daytime - 1 1 0 / 1 1 1
    Stop();
  }
}

void ClosingState::Start()
{
  context->logger->Info(Messages::SW_CLOSING_DOOR);
  closing = true;
  context->lcd->DisplayClosing();
  context->ring->Start();
  context->motor->GoBackward(15000);
}

void ClosingState::Stop()
{
  context->logger->Info(Messages::SW_CLOSING_STOP);
  closing = false;
  context->lcd->TurnOff();
  context->ring->Stop();
  context->motor->Stop();
}

void ClosingState::Setup()
{
  closing = false;
}