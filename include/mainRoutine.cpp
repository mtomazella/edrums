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

#define DOUBLE_BASS_SELECTOR_PIN 19

namespace MainRoutine
{
  void setup()
  {
    MIDI.begin(MIDI_CHANNEL);
    Serial.begin(115200);

    pinMode(DOUBLE_BASS_SELECTOR_PIN, INPUT_PULLUP);

    snare.setCurve(SNARE[5]);
    hihat.setCurve(HIHAT_OPEN[5]);
    ride.setCurve(RIDE[5]);
    crash.setCurve(CRASH[5]);
    bass.setCurve(BASS[5]);

    hh_pedal.velocity = 50;

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

    bool doubleBassEnabled = digitalRead(DOUBLE_BASS_SELECTOR_PIN) == LOW;

    readAndSend(snare, SNARE);
    readAndSend(crash, CRASH);
    // readAndSend(ride, RIDE);
    readAndSend(bass, BASS);

    if (doubleBassEnabled)
    {
      readAndSend(bass2, BASS2);
    }
    else
    {
      if (hh_pedal.hit)
        MIDI.sendNoteOff(HIHAT_OPEN[4], 0, MIDI_CHANNEL);
      readAndSend(hh_pedal, HH_PEDAL);
    }

    if (doubleBassEnabled || hh_pedal.pressed)
    {
      readAndSend(hihat, HIHAT_CLOSED);
    }
    else
    {
      readAndSend(hihat, HIHAT_OPEN);
    }
  }
}