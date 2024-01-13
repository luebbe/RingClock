#pragma once

#include "LedEffect.h"
#include "debugutils.h"
#include "TypeDefs.h"

class ClockSimple : public LedEffect
{
private:
  TGetTimeFunction _onGetTime;

public:
  explicit ClockSimple(CRGB *leds, uint16_t count, TGetTimeFunction onGetTime);

  void init() override;
  bool paint(bool force) override;
};
