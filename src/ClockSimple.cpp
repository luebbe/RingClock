#include "ClockSimple.h"

ClockSimple::ClockSimple(CRGB *leds, uint16_t count, TGetTimeFunction onGetTime)
    : LedEffect(leds, count), _onGetTime(onGetTime)
{
}

void ClockSimple::init()
{
  memset8(_leds, 0, sizeof(struct CRGB) * _numLeds);
}

bool ClockSimple::paint(bool force)
{
  uint64_t now = millis();
  if (force || (now - _lastUpdate >= UPDATE_MS) || (_lastUpdate == 0))
  {
    _lastUpdate = now;

    int hours;
    int minutes;
    int seconds;

    if (_onGetTime(hours, minutes, seconds))
    {
      memset8(_leds, 0, sizeof(struct CRGB) * _numLeds);

      hours = hours % 12;         // Convert to 12 hours
      hours = hours ? hours : 12; // Make midnight -> 12 o'clock
      int hourLeds = hours * 5;   // + minutes / 12; // Each hour has 5 LEDs, each minute adds 1/12 to an hour

      setPixel(hourLeds, CRGB::LimeGreen);
      setPixel(minutes, CRGB::DarkBlue);
      setPixel(seconds, CRGB::DeepPink);

      return true;
    }
  }
  return false;
}
