#include <Arduino.h>

#define PIN 33
#define THRESHOLD 250

namespace GraphRoutine
{
  void setup()
  {
    Serial.begin(115200);
  }

  void loop()
  {
    uint16_t value = analogRead(PIN) / 4;
    if (value >= THRESHOLD)
      Serial.println(value);
  }
}