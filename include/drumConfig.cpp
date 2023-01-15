#include <Arduino.h>
#include <hellodrum.h>

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