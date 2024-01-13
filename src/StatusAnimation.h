/*
 * Status overlay using the LedMatrix base class.
 * 
 * Version: 1.0
 * Author: Lübbe Onken (http://github.com/luebbe)
 */

#pragma once

#include "LedEffect.h"

enum CLOCK_STATUS
{
    SETUP,
    WIFI_DISCONNECTED,
    WIFI_CONNECTED,
    MQTT_DISCONNECTED,
    MQTT_CONNECTED
};

class StatusAnimation : public LedEffect
{
private:
    CLOCK_STATUS _status = CLOCK_STATUS::SETUP;
    unsigned long _lastUpdate;

public:
    explicit StatusAnimation(CRGB *leds, uint16_t count);

    void init(){};
    bool paint(bool force) override;
    void setStatus(CLOCK_STATUS status) { _status = status; };
};
