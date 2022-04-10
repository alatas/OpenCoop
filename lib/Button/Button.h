#ifndef __BUTTON_H
#define __BUTTON_H

#include <Arduino.h>
#include <Component.h>
#include <Context.h>
#include <Logger.h>
#include <RTC.h>

class Button : public Component
{

private:
  int pin = 0;
  int idleState;
  unsigned long changeStarted = 0;
  int shortPress = 50;
  int longPress = 500;
  int state = 0;
  String name;

public:
  Button(Context *context, String name, unsigned int pin, int initialState = HIGH);

  void Setup() override;
  void Loop() override;

  bool IsPressed();
  bool IsLongPressed();
};
#endif