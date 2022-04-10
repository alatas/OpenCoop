#ifndef __DAYTIMESTATE_H
#define __DAYTIMESTATE_H

#include <Arduino.h>
#include <Context.h>
#include <RTC.h>
#include <Button.h>
#include <LCD.h>
#include <State.h>

class DaytimeState : State
{
public:
  DaytimeState(Context *context) : State(context){};

  void Setup() override;
  void Loop() override;
};
#endif