#pragma once
#include <Arduino.h>
#include "Queue.hpp"

class Drum
{
public:
  String name;
  uint8_t triggerPin;
  uint8_t velocityPin;
  int midiCode;
  Queue *queue;
  long lastTrigger = 0;

  Drum(String name, uint8_t triggerPin, uint8_t velocityPin, int midiCode, Queue *queue)
  {
    this->name = name;
    this->triggerPin = triggerPin,
    this->velocityPin = velocityPin,
    this->midiCode = midiCode;
    this->queue = queue;

    pinMode(triggerPin, INPUT_PULLUP);
  }

  bool isBounce(long time)
  {
    return time - lastTrigger < 100;
  }

  void onTrigger()
  {
    long time = millis();
    if (isBounce(time))
      return;
    queue->add(new QueueItem(midiCode, map(analogRead(velocityPin), 0, 4095, 0, 127)));

    lastTrigger = time;
  }
};