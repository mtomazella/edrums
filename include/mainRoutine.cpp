#include <Arduino.h>
#include <MIDI.h>

#include "drumConfig.cpp"

#define MIDI_CHANNEL 1
MIDI_CREATE_DEFAULT_INSTANCE();

#define readAndSend(drum, config)                               \
  drum.singlePiezo(config[0], config[1], config[2], config[3]); \
  if (drum.hit == true)                                         \
    MIDI.sendNoteOn(config[4], drum.velocity, MIDI_CHANNEL);

namespace MainRoutine
{
  void setup()
  {
    MIDI.begin(MIDI_CHANNEL);
    Serial.begin(115200);

    snare.setCurve(SNARE[5]);
    hihat.setCurve(HIHAT[5]);
    ride.setCurve(RIDE[5]);
    crash.setCurve(CRASH[5]);
  }

  void loop()
  {
    readAndSend(snare, SNARE);
    readAndSend(hihat, HIHAT);
    readAndSend(crash, CRASH);
    // readAndSend(ride, RIDE);
  }
}