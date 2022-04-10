#ifndef __MOTOR_H
#define __MOTOR_H

#include <Arduino.h>
#include <Component.h>
#include <Context.h>
#include <Logger.h>
#include <L298N.h>

class Motor : public Component
{

private:
  L298N *motor{nullptr};
  uint8_t driverPin1 = 0;
  uint8_t driverPin2 = 0;

  int8_t state = 0;
  unsigned long stop = 0;

public:
  Motor(Context *context, uint8_t driverPin1, uint8_t driverPin2);

  void Setup() override;
  void Loop() override;

  void GoForward(int duration);
  void GoBackward(int duration);
  void Stop();
  bool IsMoving();
};
#endif