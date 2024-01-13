#include "OtaHelper.h"

OtaHelper::OtaHelper(CRGB *leds, uint16_t count)
    : LedEffect(leds, count)
{
}

void OtaHelper::onStart()
{
  FastLED.clear(true);
}

void OtaHelper::onEnd()
{
  for (uint8_t i = 0; i < _numLeds; i++)
    _leds[i] = CRGB::LimeGreen;
  FastLED.show();
}

void OtaHelper::onError(ota_error_t error)
{
  if (error == OTA_AUTH_ERROR)
  {
    Serial.println(F("Auth Failed"));
  }
  else if (error == OTA_BEGIN_ERROR)
  {
    Serial.println(F("Begin Failed"));
  }
  else if (error == OTA_CONNECT_ERROR)
  {
    Serial.println(F("Connect Failed"));
  }
  else if (error == OTA_RECEIVE_ERROR)
  {
    Serial.println(F("Receive Failed"));
  }
  else if (error == OTA_END_ERROR)
  {
    Serial.println(F("End Failed"));
  }
  else
  {
    Serial.println(F("Unknown Error"));
  }
}

void OtaHelper::onProgress(unsigned int progress, unsigned int total)
{
  float_t curProgress = float_t(progress * _numLeds) / total;
  uint8_t brightness = int(curProgress * 256) % 256;
  uint8_t index = uint8_t(curProgress);

  // 100% would lead to overflow, just draw the bar until 99%
  if (index < _numLeds)
    _leds[index] = CHSV(HUE_PURPLE, 100, brightness);

  FastLED.show();
}

void OtaHelper::init()
{
  ArduinoOTA.onStart([this]()
                     { onStart(); });

  ArduinoOTA.onEnd([this]()
                   { onEnd(); });

  ArduinoOTA.onProgress([this](unsigned int progress, unsigned int total)
                        { onProgress(progress, total); });

  ArduinoOTA.onError([this](ota_error_t error)
                     { onError(error); });

  // This is less of a security measure and more a accidential flash prevention
  // ArduinoOTA.setPassword(identifier);

  ArduinoOTA.begin();
}

bool OtaHelper::paint(bool force)
{
  return false;
}