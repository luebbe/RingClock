#include "ClockAdafruit.h"

ClockAdafruit::ClockAdafruit(CRGB *leds, uint16_t count, TGetTimeFunction onGetTime)
    : LedEffect(leds, count), _onGetTime(onGetTime)
{
}

void ClockAdafruit::init()
{
  memset8(_leds, 0, sizeof(struct CRGB) * _numLeds);
}

bool ClockAdafruit::paint(bool force)
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
      uint8_t red, green, blue;

      memset8(_leds, 0, sizeof(struct CRGB) * _numLeds);

      hours = hours % 12;         // Convert to 12 hours
      hours = hours ? hours : 12; // Make midnight -> 12 o'clock

      hours = (hours * 60 + minutes) / 12; // each red dot represent 24 minutes.

      // arc mode
      for (uint8_t i = 0; i < _numLeds; i++)
      {

        if (i <= seconds)
        {
          // calculates a faded arc from low to maximum brightness
          blue = (i + 1) * (255 / (seconds + 1));
          // blue = 255;
        }
        else
        {
          blue = 0;
        }

        if (i <= minutes)
        {
          green = (i + 1) * (255 / (minutes + 1));
          // green = 255;
        }
        else
        {
          green = 0;
        }

        if (i <= hours)
        {
          red = (i + 1) * (255 / (hours + 1));
          // red = 255;
        }
        else
        {
          red = 0;
        }

        setPixel(i, CRGB(red, green, blue));
      }

      return true;
    }
  }
  return false;
}

// byte pixelColorRed, pixelColorGreen, pixelColorBlue; // holds color values

// // nighttime dimming constants
// // brightness based on time of day- could try warmer colors at night?
// #define DAYBRIGHTNESS 64
// #define NIGHTBRIGHTNESS 20

// // cutoff times for day / night brightness. feel free to modify.
// #define MORNINGCUTOFF 7  // when does daybrightness begin?   7am
// #define NIGHTCUTOFF 22 // when does nightbrightness begin? 10pm

// void loop () {

//   // get time
//   DateTime theTime = dst_rtc.calculateTime(rtc.now()); // takes into account DST

//   byte secondval = theTime.second();  // get seconds
//   byte minuteval = theTime.minute();  // get minutes
//   int hourval = theTime.hour();   // get hours

//   // change brightness if it's night time
//   // check less often, once per minute
//   if (secondval == 0) {
//     if (hourval < MORNINGCUTOFF || hourval >= NIGHTCUTOFF) {
//       strip.setBrightness(NIGHTBRIGHTNESS);
//     } else {
//       strip.setBrightness(DAYBRIGHTNESS);
//     }
//   }

//   hourval = hourval % 12; // This clock is 12 hour, if 13-23, convert to 0-11`

//   hourval = (hourval * 60 + minuteval) / 12; //each red dot represent 24 minutes.

//   // arc mode
//   for (uint8_t i = 0; i < strip.numPixels(); i++) {

//     if (i <= secondval) {
//       // calculates a faded arc from low to maximum brightness
//       pixelColorBlue = (i + 1) * (255 / (secondval + 1));
//       //pixelColorBlue = 255;
//     }
//     else {
//       pixelColorBlue = 0;
//     }

//     if (i <= minuteval) {
//       pixelColorGreen = (i + 1) * (255 / (minuteval + 1));
//       //pixelColorGreen = 255;
//     }
//     else {
//       pixelColorGreen = 0;
//     }

//     if (i <= hourval) {
//       pixelColorRed = (i + 1) * (255 / (hourval + 1));
//       //pixelColorRed = 255;
//     }
//     else {
//       pixelColorRed = 0;
//     }

//     strip.setPixelColor((i + STARTPIXEL) % 60, strip.Color(pixelColorRed, pixelColorGreen, pixelColorBlue));
//   }

//   //display
//   strip.show();

//   // printTheTime(theTime);

//   // wait
//   delay(100);

// }

// // Fill the dots one after the other with a color
// void colorWipe(uint32_t c, uint8_t wait) {
//   for (uint16_t i = 0; i < strip.numPixels(); i++) {
//     //strip.setPixelColor(i, c);
//     strip.setPixelColor((i + STARTPIXEL) % 60, c);
//     strip.show();
//     delay(wait);
//   }
// }
