#pragma once

#include "LedEffect.h"
#include "debugutils.h"
#include "TypeDefs.h"

class ClockLight : public LedEffect
{
private:
  CHSV hourcolor = CHSV(64, 255, 255);    // yellow
  CHSV minutecolor = CHSV(160, 255, 255); // blue
  uint8_t blendpoint = 256 * 40 / 100;    // level of default blending (percent value normalized to 256ths)

  TGetTimeFunction _onGetTime;

  void face(uint16_t hour_pos, uint16_t min_pos);

public:
  explicit ClockLight(CRGB *leds, uint16_t count, TGetTimeFunction onGetTime);

  void init() override;
  bool paint(bool force) override;
};
