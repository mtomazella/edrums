#include <Arduino.h>

#define ROUTINE_MAIN

// Routine that reads the pin and outputs
// the result to the serial in a plottable
// manner if it excedes a threshold
// #define ROUTINE_GRAPH

#ifdef ROUTINE_GRAPH
#include "graphRoutine.cpp"
#define namespace GraphRoutine
#else
#include "mainRoutine.cpp"
#define namespace MainRoutine
#endif

void setup()
{
  namespace ::setup();
}
void loop()
{
  namespace ::loop();
}