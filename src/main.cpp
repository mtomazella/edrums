#include <Arduino.h>
#include <MIDI.h>

#include "Queue.hpp"
#include "Drum.hpp"

#define MIDI_CHANNEL 1

MIDI_CREATE_DEFAULT_INSTANCE();

Queue *queue = new Queue();

Drum snare = Drum("Snare", 23, 15, 40, queue);

void interruptHandler(void *drum)
{
  ((Drum *)drum)->onTrigger();
}

void setup()
{
  MIDI.begin(MIDI_CHANNEL);
  Serial.begin(115200);

  attachInterruptArg(snare.triggerPin, interruptHandler, &snare, FALLING);
}

void loop()
{
  QueueItem *item = queue->shift();
  if (item == NULL)
    return;
  MIDI.sendNoteOn(item->pitch, item->velocity, MIDI_CHANNEL);
  MIDI.sendNoteOff(item->pitch, 0, MIDI_CHANNEL);
}