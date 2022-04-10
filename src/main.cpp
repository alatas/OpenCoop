#include <Arduino.h>
#include "OpenCoop.h"

OpenCoop coop;

void setup()
{
  coop.Setup();
}

void loop()
{
  coop.Loop();
}