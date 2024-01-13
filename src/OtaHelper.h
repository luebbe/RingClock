#pragma once

#include <ArduinoOTA.h>
#include "LedEffect.h"

class OtaHelper : public LedEffect
{
private:
  void onStart();
  void onEnd();
  void onError(ota_error_t error);
  void onProgress(unsigned int progress, unsigned int total);

public:
  explicit OtaHelper(CRGB *leds, uint16_t count);

  void init() override;
  bool paint(bool force) override;
};
