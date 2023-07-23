#include <Arduino.h>
#include <MIDI.h>

#include "Drum.hpp"
#include "drumsSetup.hpp"
#include "menu.cpp"

#define MIDI_CHANNEL 1
MIDI_CREATE_DEFAULT_INSTANCE();

#define DOUBLE_BASS_SELECTOR_PIN 19

namespace MainRoutine
{
  void setup()
  {
    MIDI.begin(MIDI_CHANNEL);
    Serial.begin(115200);

    pinMode(DOUBLE_BASS_SELECTOR_PIN, INPUT_PULLUP);

    setupDrumDefaults();
    Menu::setup();
  }

  template <typename DrumT>
  void readAndSend(EDrum<DrumT> drum, byte noteToOff = 0)
  {
    DrumSenseInformation result = drum.sense();
    if (result.hit == true)
    {
      MIDI.sendNoteOn(drum.note, result.velocity, MIDI_CHANNEL);
      if (noteToOff != 0)
        MIDI.sendNoteOff(noteToOff, 0, MIDI_CHANNEL);
    }
  }

  void loop()
  {
    Menu::loop();

    bool doubleBassEnabled = digitalRead(DOUBLE_BASS_SELECTOR_PIN) == LOW;

    readAndSend(SNARE);
    readAndSend(CRASH);
    readAndSend(BASS);

    if (doubleBassEnabled)
      readAndSend(BASS2);
    else
      readAndSend(HH_PEDAL, HIHAT_OPEN.note);

    if (doubleBassEnabled || HH_PEDAL.isPressed())
      readAndSend(HIHAT_CLOSED);
    else
      readAndSend(HIHAT_OPEN);
  }
}