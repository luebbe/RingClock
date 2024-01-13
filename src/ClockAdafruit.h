#pragma once

#include "LedEffect.h"
#include "debugutils.h"
#include "TypeDefs.h"

class ClockAdafruit : public LedEffect
{
private:
  TGetTimeFunction _onGetTime;

public:
  explicit ClockAdafruit(CRGB *leds, uint16_t count, TGetTimeFunction onGetTime);

  void init() override;
  bool paint(bool force) override;
};
