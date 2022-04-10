#ifndef __CLOSINGSTATE_H
#define __CLOSINGSTATE_H

#include <Arduino.h>
#include <Context.h>
#include <RTC.h>
#include <Button.h>
#include <LCD.h>
#include <Motor.h>
#include <Ring.h>
#include <State.h>

class ClosingState : State
{
private:
  bool closing = false;

public:
  ClosingState(Context *context) : State(context){};

  void Setup() override;
  void Loop() override;

  void Start();
  void Stop();
};
#endif