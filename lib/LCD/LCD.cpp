#include "LCD.h"

LCD::LCD(Context *context, uint8_t clkPin, uint8_t ioPin, uint8_t brightness = 2) : Component(context)
{
  this->brightness = brightness;
  this->clkPin = clkPin;
  this->ioPin = ioPin;
}

void LCD::Setup()
{
  if (!tm)
    tm = new TM1637Display{clkPin, ioPin};

  tm->clear();
  tm->setBrightness(brightness);
  context->logger->Info(Messages::LCD_INIT);
}

void LCD::Loop()
{
  if (state)
  {
    if (useColon)
    {
      bool colon = ((int)round(millis() / 1000.0) % 2 == 0);

      if (colon && !colonState)
      {

        colonState = true;
        DisplayTime(true);
      }
      else if (!colon && colonState)
      {
        colonState = false;
        DisplayTime(false);
      }
    }

    if (blinkingMsec > 0)
    {
      bool display = ((int)round(millis() / blinkingMsec) % 2 == 0);

      if (display && !displayState)
      {
        displayState = true;
        tm->setSegments(recent_seg);
      }
      else if (!display && displayState)
      {
        displayState = false;
        tm->clear();
      }
    }
  }
}

void LCD::DisplayTime(uint8_t hour, uint8_t minute)
{
  uint16_t displayTime_ = (hour * 100) + minute;

  if (displayTime_ == displayTime)
    return;

  useColon = true;
  this->displayTime = displayTime_;

  onMode();

  context->logger->Debug(Messages::LCD_DISP_TIME);
  DisplayTime(true);
}

void LCD::DisplayTime(bool colon)
{
  state = true;
  blinkingMsec = 0;

  if (colon)
    tm->showNumberDecEx(displayTime, 0b11100000, true);
  else
    tm->showNumberDecEx(displayTime, 0, true);
}

void LCD::DisplayOpening()
{
  context->logger->Debug(Messages::LCD_DISP_OPENING);
  displaySegment(open_seg, "Opening");
}

void LCD::DisplayClosing()
{
  context->logger->Debug(Messages::LCD_DISP_CLOSING);
  displaySegment(close_seg, "Closing");
}

void LCD::TurnOff()
{
  if (!state)
    return;

  state = false;
  useColon = false;
  displayTime = 0;

  offMode();
  context->logger->Debug(Messages::LCD_DISP_CLEAR);
}