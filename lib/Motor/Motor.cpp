#include "Motor.h"

Motor::Motor(Context *context, uint8_t driverPin1, uint8_t driverPin2) : Component(context)
{
  this->driverPin1 = driverPin1;
  this->driverPin2 = driverPin2;
}

void Motor::Setup()
{
  if (!motor)
    motor = new L298N{driverPin1, driverPin2};

  context->logger->Info(Messages::MOTOR_INIT);
}

void Motor::Loop()
{
  if (millis() >= stop && state != 0)
  {
    Stop();
  }
}

void Motor::GoForward(int duration)
{
  if (state == 1)
    return;

  state = 1;
  stop = millis() + duration;
  motor->forward();
  context->logger->Debug(Messages::MOTOR_FORWARD);
}

void Motor::GoBackward(int duration)
{
  if (state == -1)
    return;

  state = -1;
  stop = millis() + duration;
  motor->backward();
  context->logger->Debug(Messages::MOTOR_BACKWARD);
}

void Motor::Stop()
{
  if (state == 0)
    return;

  state = 0;
  stop = 0;
  motor->stop();
  context->logger->Debug(Messages::MOTOR_STOPPED);
}

bool Motor::IsMoving()
{
  return (state != 0);
}