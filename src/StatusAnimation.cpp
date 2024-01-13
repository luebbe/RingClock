/*
 * Status overlay using the LedMatrix base class.
 *
 * Version: 1.0
 * Author: Lübbe Onken (http://github.com/luebbe)
 */

#include "StatusAnimation.h"

StatusAnimation::StatusAnimation(CRGB *leds, uint16_t count)
    : LedEffect(leds, count)
{
}

bool StatusAnimation::paint(bool force)
{
  uint64_t now = millis();
  if ((now - _lastUpdate >= UPDATE_MS) || (_lastUpdate == 0))
  {
    _lastUpdate = now;
    uint8_t index = uint8_t(round(now / 250)) % 4 * 15;

    switch (_status)
    {
    case CLOCK_STATUS::SETUP:
    case CLOCK_STATUS::WIFI_DISCONNECTED:
      _leds[index] = CRGB::Azure;
      return true;
    case CLOCK_STATUS::WIFI_CONNECTED:
    case CLOCK_STATUS::MQTT_DISCONNECTED:
      _leds[index] = CRGB::Magenta;
      return true;
    case CLOCK_STATUS::MQTT_CONNECTED:
      return false;
    default:
      return false;
    }
  }
  return false;
}
