#include <Arduino.h>
#include <MIDI.h>
#include <hellodrum.h>

#define MIDI_CHANNEL 1
MIDI_CREATE_DEFAULT_INSTANCE();

#define readAndSend(drum, config)                               \
  drum.singlePiezo(config[0], config[1], config[2], config[3]); \
  if (drum.hit == true)                                         \
    MIDI.sendNoteOn(config[4], drum.velocity, MIDI_CHANNEL);

byte SNARE[7] = {
    80, // sensitivity
    10, // threshold
    20, // scantime
    20, // masktime
    38, // note
    1,  // curve type
    33  // pin
};
HelloDrum snare(SNARE[6]);
byte HIHAT[7] = {
    100, // sensitivity
    10,  // threshold
    20,  // scantime
    50,  // masktime
    42,  // note
    1,   // curve type
    32   // pin
};
HelloDrum hihat(HIHAT[6]);
byte RIDE[7] = {
    80, // sensitivity
    10, // threshold
    20, // scantime
    50, // masktime
    51, // note
    1,  // curve type
    34  // pin
};
HelloDrum ride(RIDE[6]);
byte CRASH[7] = {
    50, // sensitivity
    10, // threshold
    20, // scantime
    50, // masktime
    49, // note
    1,  // curve type
    35  // pin
};
HelloDrum crash(CRASH[6]);

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