#pragma once

#include "Drum.hpp"

EDrum<HelloDrum> SNARE = EDrum<HelloDrum>(
    "Snare",
    60, // sensitivity
    5,  // threshold
    20, // scantime
    20, // masktime
    40, // note (0-127)
    1,  // curve type (0-4)
    25  // pin
);

EDrum<HelloDrum> HIHAT_OPEN = EDrum<HelloDrum>(
    "HH Open",
    60, // sensitivity
    15, // threshold
    20, // scantime
    70, // masktime
    46, // note
    2,  // curve type
    26  // pin
);

EDrum<HelloDrum> HIHAT_CLOSED = EDrum<HelloDrum>(
    "HH Closed",
    60, // sensitivity
    5,  // threshold
    20, // scantime
    50, // masktime
    42, // note
    2,  // curve type
    26  // pin
);

EDrum<HelloDrum> RIDE = EDrum<HelloDrum>(
    "Ride",
    80, // sensitivity
    5,  // threshold
    20, // scantime
    50, // masktime
    51, // note
    1,  // curve type
    27  // pin
);

EDrum<HelloDrum> CRASH = EDrum<HelloDrum>(
    "Crash",
    70, // sensitivity
    10, // threshold
    20, // scantime
    50, // masktime
    39, // note
    1,  // curve type
    14  // pin
);

EDrum<Pedal> BASS = EDrum<Pedal>(
    "Bass",
    0,   // sensitivity
    0,   // threshold
    0,   // scantime
    20,  // masktime
    36,  // note
    0,   // curve type
    18,  // pin
    true // isPedal
);

EDrum<Pedal> BASS2 = EDrum<Pedal>(
    "Bass 2",
    0,   // sensitivity
    0,   // threshold
    0,   // scantime
    50,  // masktime
    36,  // note
    0,   // curve type
    0,   // pin
    true // isPedal
);

EDrum<Pedal> HH_PEDAL = EDrum<Pedal>(
    "HH Pedal",
    0,   // sensitivity
    0,   // threshold
    0,   // scantime
    20,  // masktime
    44,  // note
    0,   // curve
    23,  // pin
    true // isPedal
);

void setupDrumDefaults()
{
    HH_PEDAL.fixVelocity(50);
}

#define NUM_DRUMS 5
#define NUM_PEDALS 3
EDrum<HelloDrum> *DRUMS[NUM_DRUMS] = {&SNARE, &HIHAT_CLOSED, &HIHAT_OPEN, &CRASH, &RIDE};
EDrum<Pedal> *PEDALS[NUM_PEDALS] = {&HH_PEDAL, &BASS, &BASS2};