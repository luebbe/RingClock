
/*
 * base class to display animations on a LED strip
 *
 * Author: Lübbe Onken (http://github.com/luebbe)
 */

#pragma once

#include <FastLED.h>
#include "debugutils.h"

#define STARTPIXEL 0 // To be able to adjust the starting position of the first pixel
#define UPDATE_MS 50 // Update the display 20 times per second in order to follow the brightness changes quickly enough

class LedEffect
{
protected:
	CRGB *const _leds;
	const uint16_t _numLeds;
	CRGBPalette16 _currentPalette;
	unsigned long _lastUpdate;

	CRGB getRandomColor();
	CRGB getColorFromPalette(uint8_t index);

public:
	explicit LedEffect(CRGB *leds, uint16_t count);
	virtual ~LedEffect();

	virtual void init();
	virtual bool paint(bool force) = 0;

	void setPalette(CRGBPalette16 value)
	{
		_currentPalette = value;
		paint(true);
	}
	void setPixel(int index, uint8_t r, uint8_t g, uint8_t b)
	{
		DEBUG_PRINTF("%d %d %d", r, g, b);

		_leds[(index + STARTPIXEL) % 60] = CRGB(r, g, b);
	}

	void setPixel(int index, CRGB color)
	{
		DEBUG_PRINTF("%d %d %d", color.r, color.g, color.b);

		_leds[(index + STARTPIXEL) % 60] = color;
	}
};
