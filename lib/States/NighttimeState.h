#ifndef __NIGHTTTIMESTATE_H
#define __NIGHTTIMESTATE_H

#include <Arduino.h>
#include <Context.h>
#include <RTC.h>
#include <Button.h>
#include <LCD.h>
#include <State.h>

class NighttimeState : State
{
public:
  NighttimeState(Context *context) : State(context){};

  void Setup() override;
  void Loop() override;
};
#endif