#include <Arduino.h>
#include <hellodrum.h>
#include "BassPedal.cpp"

// byte SNARE[12] = {
//     100, // sensitivity (1-100)
//     10,  // threshold (1-100)
//     30,  // scan time (1-100)
//     10,  // mask time (1-100)
//     3,   // rim sensitivity (1-100)
//     3,   // rim threshold (1-100)
//     1,   // curve type (0-4)
//     38,  // note (0-127)
//     40,  // note of rim shot (0-127)
//     37,  // note of cross stick (0-127)
//     14,  // pin
//     25   // pin rim
// };
// HelloDrum snare(SNARE[10], SNARE[11]);
byte SNARE[7] = {
    70, // sensitivity
    5,  // threshold
    20, // scantime
    20, // masktime
    38, // note (0-127)
    1,  // curve type (0-4)
    14, // pin
};
HelloDrum snare(SNARE[6]);

byte HIHAT[7] = {
    60, // sensitivity
    5,  // threshold
    20, // scantime
    50, // masktime
    42, // note
    2,  // curve type
    27  // pin
};
HelloDrum hihat(HIHAT[6]);

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
    25  // pin
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
BassPedal bass(BASS[6]);