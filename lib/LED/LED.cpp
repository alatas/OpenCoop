#include "LED.h"

LED::LED(Context *context, int pin) : Component(context)
{
  this->pin = pin;
}

void LED::Setup()
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  state = false;
  mode = -1;
  context->logger->Info(Messages::LED_INIT);
}

void LED::Loop()
{
  if (mode < 0 && state)
  {
    digitalWrite(pin, LOW);
    state = false;
  }
  else if (mode == 0 && !state)
  {
    digitalWrite(pin, HIGH);
    state = true;
  }
  else if (mode > 0 && millis() >= lastChange + mode)
  {
    lastChange = millis();
    state = !state;
    digitalWrite(pin, (int)state);
  }
}

void LED::TurnOn(int blinkingMsec = 0)
{
  if (mode == blinkingMsec)
    return;
  context->logger->Debug(Messages::LED_ON);
  mode = blinkingMsec;
  lastChange = 0;
}

void LED::TurnOff()
{
  if (mode == -1)
    return;
  context->logger->Debug(Messages::LED_OFF);
  mode = -1;
}