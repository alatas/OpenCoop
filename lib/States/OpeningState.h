#ifndef __OPENINGSTATE_H
#define __OPENINGSTATE_H

#include <Arduino.h>
#include <Context.h>
#include <RTC.h>
#include <Button.h>
#include <LCD.h>
#include <Motor.h>
#include <Ring.h>

#include <State.h>

class OpeningState : State
{
private:
  bool opening = false;

public:
  OpeningState(Context *context) : State(context){};

  void Setup() override;
  void Loop() override;

  void Start();
  void Stop();
};
#endif