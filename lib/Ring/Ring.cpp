#include "Ring.h"

Ring::Ring(Context *context, uint8_t pin) : Component(context)
{
  this->pin = pin;
}

void Ring::Setup()
{
  Bebebep(100);
  context->logger->Info(Messages::RING_INIT);
}

void Ring::Loop()
{

  if (!state)
    return;

  if (next <= millis())
  {
    noTone(pin);
    delay(pauseBetweenNotes);

    index++;
    if (index >= tuneSize)
      index = 0;

    int noteDuration = (int)((1000 * (60 * 4 / tempo)) / durations[index] + 0.);
    pauseBetweenNotes = noteDuration * 0.20;
    next = millis() + noteDuration;
    tone(pin, melody[index], noteDuration);
  }
}

void Ring::Start()
{

  if (state)
    return;

  next = 0;
  index = 0;
  state = true;
  context->logger->Debug(Messages::RING_STARTED);
}

void Ring::Stop()
{
  state = false;
  context->logger->Debug(Messages::RING_STOPPED);
}

void Ring::Bebebep(uint16_t duration)
{

  if (state)
    return;

  context->logger->Debug(Messages::RING_BEEP);

  state = true;
  tone(pin, NOTE_A4, duration);
  delay(duration);
  noTone(duration);
  delay(duration);
  tone(pin, NOTE_G5, duration);
  delay(duration);
  noTone(duration);
  delay(duration);
  tone(pin, NOTE_A4, duration);
  delay(duration);
  noTone(duration);
  delay(duration);
  state = false;
}