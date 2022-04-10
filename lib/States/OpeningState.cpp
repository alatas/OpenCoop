#include "OpeningState.h"

void OpeningState::Loop()
{
  bool isDaytime = context->rtc->IsDaytime();

  if (!opening && !isDaytime)
  {
    // not opening, night and door is not opened - 0 0 0 / 0 0 1
    context->logger->Info(Messages::SW_NIGHTTIME_STATE);
    context->TransitionTo(context->nighttimeState);
  }
  else if ((!opening && isDaytime && !context->upper->IsPressed()))
  {
    // not opening, daytime, door is not opened - 0 1 0
    Start();
  }
  else if (!opening && isDaytime && context->upper->IsPressed())
  {
    // not opening, daytime, door is opened- 0 1 1
    context->logger->Info(Messages::SW_DAYTIME_STATE);
    context->TransitionTo(context->daytimeState);
  }
  else if (opening && !isDaytime)
  {
    // opening and night - 1 0 0 / 1 0 1
    Stop();
  }
  else if (opening && isDaytime && !context->upper->IsPressed())
  {
    // opening and daytime and door is not opened - 1 1 0
    // wait
    if (!context->motor->IsMoving())
    {
      // timeout
      Stop();
      context->TransitionTo(context->daytimeState);
    }
  }
  else if (opening && isDaytime && context->upper->IsPressed())
  {
    // opening and daytime and door is opened - 1 1 1
    Stop();
  }
}

void OpeningState::Start()
{
  context->logger->Info(Messages::SW_OPENING_DOOR);
  opening = true;
  context->lcd->DisplayOpening();
  context->ring->Start();
  context->motor->GoForward(15000);
}

void OpeningState::Stop()
{
  context->logger->Info(Messages::SW_OPENING_STOP);
  opening = false;
  context->lcd->TurnOff();
  context->ring->Stop();
  context->motor->Stop();
}

void OpeningState::Setup()
{
  opening = false;
}