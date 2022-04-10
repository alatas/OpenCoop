#ifndef __LCD_H
#define __LCD_H

#include <Arduino.h>
#include <Component.h>
#include <Context.h>
#include <Logger.h>
#include <TM1637Display.h>

class LCD : public Component
{

private:
  uint8_t clkPin = 0;
  uint8_t ioPin = 0;
  uint8_t brightness = 2;

  bool state = false;
  bool useColon = false;

  bool colonState = false;
  bool displayState = false;

  uint16_t displayTime = 0;

  TM1637Display *tm{nullptr};
  uint16_t blinkingMsec;

  uint8_t *recent_seg;

  uint8_t open_seg[4] = {
      SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, // O
      SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,         // P
      SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,         // E
      SEG_A | SEG_B | SEG_C | SEG_E | SEG_F          // N
  };

  uint8_t close_seg[4] = {
      SEG_A | SEG_D | SEG_E | SEG_F,         // C
      SEG_D | SEG_E | SEG_F,                 // L
      SEG_A | SEG_C | SEG_D | SEG_F | SEG_G, // S
      SEG_A | SEG_D | SEG_E | SEG_F | SEG_G  // E
  };

  void offMode()
  {
    tm->setBrightness(brightness, false);
    tm->clear();
    delay(200);
  }

  void onMode()
  {
    tm->setBrightness(brightness, true);
    delay(200);
  }

  void displaySegment(uint8_t seg[4], String tag)
  {
    if (displayTime == 2400)
      return;

    displayTime = 2400;
    useColon = false;
    blinkingMsec = 500;
    recent_seg = seg;
    state = true;
    displayState = true;
    onMode();
    context->logger->Debug(Messages::LCD_DISP_SEG);
  }

public:
  LCD(Context *context, uint8_t clkPin, uint8_t ioPin, uint8_t brightness);

  void Setup() override;
  void Loop() override;

  void DisplayTime(uint8_t hour, uint8_t minute);
  void DisplayTime(bool colon);
  void DisplayOpening();
  void DisplayClosing();

  void TurnOff();
};
#endif