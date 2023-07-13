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

byte RIDE[7] = {
    80, // sensitivity
    5,  // threshold
    20, // scantime
    50, // masktime
    51, // note
    1,  // curve type
    0   // pin
};

byte CRASH[7] = {
    70, // sensitivity
    10, // threshold
    20, // scantime
    50, // masktime
    39, // note
    1,  // curve type
    26  // pin
};

byte BASS[7] = {
    0,  // sensitivity
    0,  // threshold
    0,  // scantime
    20, // masktime
    36, // note
    0,  // curve type
    22  // pin
};

byte BASS2[7] = {
    0,  // sensitivity
    0,  // threshold
    0,  // scantime
    50, // masktime
    36, // note
    0,  // curve type
    21  // pin
};

byte HH_PEDAL[7] = {
    0,  // sensitivity
    0,  // threshold
    0,  // scantime
    50, // masktime
    44, // note
    0,  // curve type
    21  // pin
};

HelloDrum snare(SNARE[6]);
HelloDrum hihat(HIHAT_OPEN[6]);
HelloDrum ride(RIDE[6]);
HelloDrum crash(CRASH[6]);
Pedal bass(BASS[6]);
Pedal bass2(BASS2[6]);
Pedal hh_pedal(HH_PEDAL[6]);

#define forEachDrumDo(action) \
    snare action;             \
    hihat action;             \
    ride action;              \
    crash action;             \
    bass action;              \
    bass2 action;             \
    hh_pedal action;
