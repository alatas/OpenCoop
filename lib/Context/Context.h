#ifndef __CONTEXT_H
#define __CONTEXT_H

#include <Component.h>
#include <State.h>
#include <Arduino.h>

class Button;
class Logger;
class LCD;
class LED;
class Motor;
class Ring;
class RTC;

class Context
{
private:
  Component *components[8];
  State *state;
  int lastIndex = 0;

public:
  Logger *logger = nullptr;
  Button *green = nullptr;
  Button *red = nullptr;
  Button *upper = nullptr;
  Button *lower = nullptr;
  Ring *ring = nullptr;
  LCD *lcd = nullptr;
  LED *led = nullptr;
  Motor *motor = nullptr;
  RTC *rtc = nullptr;

  State *daytimeState = nullptr;
  State *nighttimeState = nullptr;
  State *openingState = nullptr;
  State *closingState = nullptr;

  Context();

  void AddComponent(Component *);
  void Setup();
  void Loop();

  void TransitionTo(State *state)
  {
    state->Setup();
    this->state = state;
  }
};

#endif