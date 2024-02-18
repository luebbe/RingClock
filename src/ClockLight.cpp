#include "ClockLight.h"

ClockLight::ClockLight(CRGB *leds, uint16_t count, TGetTimeFunction onGetTime)
    : LedEffect(leds, count), _onGetTime(onGetTime)
{
}

void ClockLight::init()
{
  memset8(_leds, 0, sizeof(struct CRGB) * _numLeds);
}

// CHSV colorStart = CHSV(96, 235, 255);   // starting color in HSV format
// CHSV colorTarget = CHSV(192, 245, 242); // target color in HSV format
// CHSV colorCurrent = colorStart;

bool ClockLight::paint(bool force)
{
  uint64_t now = millis();
  if (force || (now - _lastUpdate >= UPDATE_MS) || (_lastUpdate == 0))
  {
    _lastUpdate = now;

    int hour;
    int minute;
    int second;

    if (_onGetTime(hour, minute, second))
    {
      memset8(_leds, 0, sizeof(struct CRGB) * _numLeds);

      uint16_t hour_pos;
      uint16_t min_pos;

      hour_pos = ((hour % 12) * _numLeds / 12 + minute * _numLeds / 720);
      min_pos = (minute * _numLeds / 60 + second * _numLeds / 3600);

      face(hour_pos, min_pos);

      setPixel(second, CRGB::White);

      return true;
    }
  }
  return false;
}

void ClockLight::face(uint16_t hour_pos, uint16_t min_pos)
{
  // this face colours the clock in 2 sections, the c1->c2 divide represents the minute hand and the c2->c1 divide represents the hour hand.
  CHSV c1;
  CHSV c1blend;
  CHSV c2;
  CHSV c2blend;

  int gap;
  int firsthand = _min(hour_pos, min_pos);
  int secondhand = _max(hour_pos, min_pos);

  // check which hand is first, so we know what colour the 0 pixel is

  if (hour_pos > min_pos)
  {
    c2 = hourcolor;   // CHSV(hourcolor);
    c1 = minutecolor; // CHSV(minutecolor);
  }
  else
  {
    c1 = hourcolor;   // CHSV(hourcolor);
    c2 = minutecolor; // CHSV(minutecolor);
  }
  // the blending is the colour that the hour/minute colour will meet. The greater the blend, the closer to the actual hour/minute colour it gets.
  c2blend = blend(c2, c1, blendpoint);
  c1blend = blend(c1, c2, blendpoint);

  // create the blend between first and 2nd hand
  gap = secondhand - firsthand;
  for (uint8_t i = firsthand; i < secondhand; i++)
  {
    fract8 bval = 256 * (i - firsthand) / gap;
    setPixel(i, blend(c2blend, c2, bval, SHORTEST_HUES));
  }

  // and the last hand
  gap = _numLeds - gap;
  for (uint8_t i = secondhand; i < _numLeds + firsthand; i++)
  {
    fract8 bval = 256 * (i - secondhand) / gap;
    setPixel(i, blend(c1blend, c1, bval));
  }
  setPixel(hour_pos, hourcolor);
  setPixel(min_pos, minutecolor);
}
