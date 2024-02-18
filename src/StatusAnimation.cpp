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
  if (force || (now - _lastUpdate >= UPDATE_MS) || (_lastUpdate == 0))
  {
    _lastUpdate = now;

    // Lässt die 0/3/6/9 LEDs leuchten
    uint8_t index = uint8_t(round(now / 250)) % 4 * 15;
    // Lässt alle LEDs leuchten
    // uint8_t index = uint8_t(round(now / 250));

    switch (_status)
    {
    case CLOCK_STATUS::SETUP:
      // DEBUG_PRINTLN("SETUP");
      setPixel(index, CRGB::Red);
      return true;
    case CLOCK_STATUS::WIFI_DISCONNECTED:
      // DEBUG_PRINTLN("WIFI_DISCONNECTED");
      setPixel(index, CRGB::Green);
      return true;
    case CLOCK_STATUS::WIFI_CONNECTED:
      // DEBUG_PRINTLN("WIFI_CONNECTED");
      setPixel(index, CRGB::Blue);
      return true;
    case CLOCK_STATUS::MQTT_DISCONNECTED:
      // DEBUG_PRINTLN("MQTT_DISCONNECTED");
      setPixel(index, CRGB::Magenta);
      return true;
    case CLOCK_STATUS::MQTT_CONNECTED:
      // DEBUG_PRINTLN("MQTT_CONNECTED");
      setPixel(index, CRGB::Yellow);
      return true;
    default:
      return false;
    }
  }
  return false;
}
