#include <Arduino.h>
#include <hellodrum.h>
#include "Pedal.cpp"

byte SNARE[7] = {
    60, // sensitivity
    5,  // threshold
    20, // scantime
    20, // masktime
    40, // note (0-127)
    1,  // curve type (0-4)
    25, // pin
};
HelloDrum snare(SNARE[6]);

byte HIHAT_OPEN[7] = {
    60, // sensitivity
    15, // threshold
    20, // scantime
    70, // masktime
    46, // note
    2,  // curve type
    33  // pin
};
byte HIHAT_CLOSED[7] = {
    60, // sensitivity
    5,  // threshold
    20, // scantime
    50, // masktime
    42, // note
    2,  // curve type
    33  // pin
};
HelloDrum hihat(HIHAT_OPEN[6]);

byte RIDE[7] = {
    80, // sensitivity
    5,  // threshold
    20, // scantime
    50, // masktime
    51, // note
    1,  // curve type
    0   // pin
};
HelloDrum ride(RIDE[6]);

byte CRASH[7] = {
    70, // sensitivity
    10, // threshold
    20, // scantime
    50, // masktime
    39, // note
    1,  // curve type
    26  // pin
};
HelloDrum crash(CRASH[6]);

byte BASS[7] = {
    0,  // sensitivity
    0,  // threshold
    0,  // scantime
    20, // masktime
    36, // note
    0,  // curve type
    22  // pin
};
Pedal bass(BASS[6]);

byte BASS2[7] = {
    0,  // sensitivity
    0,  // threshold
    0,  // scantime
    50, // masktime
    36, // note
    0,  // curve type
    21  // pin
};
Pedal bass2(BASS2[6]);

byte HH_PEDAL[7] = {
    0,  // sensitivity
    0,  // threshold
    0,  // scantime
    50, // masktime
    44, // note
    0,  // curve type
    21  // pin
};
Pedal hh_pedal(HH_PEDAL[6]);
