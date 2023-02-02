#include <Arduino.h>
#include <stdlib.h>

class Pedal
{
public:
  byte pin;
  long lastPressed = 0;
  long lastReleased = 0;
  bool hasReleased = true;
  bool hit = false;
  bool pressed = false;
  byte velocity = 127;

  Pedal(byte pin)
  {
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
  }

  void setCurve(byte curve) {}

  void singlePiezo(byte sensitivity, byte threshold, byte scantime, byte masktime)
  {
    long time = millis();
    bool pressed = digitalRead(pin) == LOW;
    this->pressed = pressed;
    bool pressedClear = time - lastPressed > masktime;
    bool releasedClear = time - lastReleased > masktime;

    if (!hit && pressed && pressedClear && hasReleased)
    {
      hit = true;
      hasReleased = false;
      lastPressed = time;
    }
    else if (hit)
    {
      hit = false;
    }

    if (!pressed && releasedClear)
    {
      hasReleased = true;
      lastReleased = time;
    }
  }
};