#include <Arduino.h>
#include <MIDI.h>
#include "Drum.hpp"
#include "drumsSetup.hpp"
#include "Menu.hpp"

#define MIDI_CHANNEL 1
MIDI_CREATE_DEFAULT_INSTANCE();

#define DOUBLE_BASS_SELECTOR_PIN 19

Menu menu;

namespace MainRoutine
{
  void setup()
  {
    MIDI.begin(MIDI_CHANNEL);
    Serial.begin(115200);

    pinMode(DOUBLE_BASS_SELECTOR_PIN, INPUT_PULLUP);

    setupDrumDefaults();

    menu.init();
  }

  template <typename DrumT>
  void readAndSend(EDrum<DrumT> *drum, byte noteToOff = 0)
  {
    DrumSenseInformation result = drum->sense();
    if (result.hit == true)
    {
      MIDI.sendNoteOn(drum->note, result.velocity, MIDI_CHANNEL);
      if (noteToOff != 0)
        MIDI.sendNoteOff(noteToOff, 0, MIDI_CHANNEL);
    }
  }

  void loop()
  {
    menu.loop();

    bool doubleBassEnabled = digitalRead(DOUBLE_BASS_SELECTOR_PIN) == LOW;

    readAndSend<HelloDrum>(&SNARE);
    readAndSend<HelloDrum>(&CRASH);
    readAndSend<HelloDrum>(&RIDE);
    readAndSend<Pedal>(&BASS);

    // if (doubleBassEnabled)
    //   readAndSend<Pedal>(&BASS2);
    // else
    readAndSend<Pedal>(&HH_PEDAL, HIHAT_OPEN.note);

    if (doubleBassEnabled || HH_PEDAL.isPressed())
      readAndSend<HelloDrum>(&HIHAT_CLOSED);
    else
      readAndSend<HelloDrum>(&HIHAT_OPEN);
  }
}