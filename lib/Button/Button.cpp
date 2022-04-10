#include "Button.h"

Button::Button(Context *context, String name, unsigned int pin, int idleState) : Component(context)
{
  this->pin = pin;
  this->idleState = idleState;
  this->name = name;
}

void Button::Setup()
{
  pinMode(pin, INPUT_PULLUP);
  context->logger->Info(Messages::BUTTON_INIT);
}

void Button::Loop()
{
  if (idleState != digitalRead(pin))
  {
    if (millis() >= changeStarted + longPress)
    {
      this->state = 2;
    }
    else if (millis() >= changeStarted + shortPress)
    {
      state = 1;
    }
    else
    {
      state = 0;
    }
  }
  else
  {
    state = 0;
    changeStarted = millis();
  }
}

bool Button::IsPressed()
{
  return (state >= 1);
}

bool Button::IsLongPressed()
{
  return (state == 2);
}