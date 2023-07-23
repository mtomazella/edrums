#pragma once

#include <hellodrum.h>
#include "Pedal.cpp"

struct DrumSenseInformation
{
    bool hit;
    byte velocity;

    DrumSenseInformation(bool hit, byte velocity) : hit(hit), velocity(velocity){};
};

template <typename DrumT>
class EDrum
{
private:
    DrumT _drum = NULL;

public:
    String name;
    byte sensitivity;
    byte threshold;
    byte scantime;
    byte masktime;
    byte note;
    byte curveType;
    byte pin;
    byte fixedVelocity = 0;
    bool isPedal;

    EDrum(
        String name,
        byte sensitivity,
        byte threshold,
        byte scantime,
        byte masktime,
        byte note,
        byte curveType,
        byte pin,
        bool isPedal = false)
    {
        this->name = name;
        this->sensitivity = sensitivity;
        this->threshold = threshold;
        this->scantime = scantime;
        this->masktime = masktime;
        this->note = note;
        this->curveType = curveType;
        this->pin = pin;
        this->isPedal = isPedal;

        this->_drum = DrumT(pin);

        this->_drum.setCurve(curveType);
    }

    void fixVelocity(byte velocity)
    {
        this->fixedVelocity = velocity;
    }

    DrumSenseInformation sense()
    {
        this->_drum.singlePiezo(this->sensitivity, this->threshold, this->scantime, this->masktime);

        return DrumSenseInformation(
            this->_drum.hit,
            this->fixedVelocity != 0 ? this->fixedVelocity : this->_drum.velocity);
    }

    bool isPressed()
    {
        if (!isPedal)
            return false;
        return ((Pedal)_drum).pressed;
    }
};
