#include <Arduino.h>
#include <MIDI.h>

#include "drumConfig.cpp"
#include "menu.cpp"

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
    bass.setCurve(BASS[5]);

    Menu::setup();
  }

  void loop()
  {
    Menu::loop();

    // snare.dualPiezo(SNARE[0], SNARE[1], SNARE[2], SNARE[3], SNARE[4], SNARE[5]); // dualPiezo(byte sens, byte thre, byte scan, byte mask, byte rimSens, byte rimThre);
    // if (snare.hit)
    //   MIDI.sendNoteOn(SNARE[7], snare.velocity, MIDI_CHANNEL); //(note, velocity, channel)
    // else if (snare.hitRim)
    // {
    //   if (snare.velocity > 60)
    //     MIDI.sendNoteOn(SNARE[8], snare.velocity, MIDI_CHANNEL); //(note, velocity, channel)
    //   else
    //     MIDI.sendNoteOn(SNARE[9], snare.velocity * 2, MIDI_CHANNEL); //(note, velocity, channel)
    // }

    readAndSend(snare, SNARE);
    readAndSend(hihat, HIHAT);
    readAndSend(crash, CRASH);
    // readAndSend(ride, RIDE);
    readAndSend(bass, BASS);
  }
}