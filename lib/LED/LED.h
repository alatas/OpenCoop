#ifndef __LED_H
#define __LED_H

#include <Arduino.h>
#include <Component.h>
#include <Context.h>
#include <Logger.h>

class LED : public Component
{

private:
  int pin = 0;
  unsigned long lastChange = 0;
  bool state = 0;
  int mode = -1;

public:
  LED(Context *context, int pin);

  void Setup() override;
  void Loop() override;

  void TurnOn(int);
  void TurnOff();
};
#endif