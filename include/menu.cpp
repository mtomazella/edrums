#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <drums.hpp>

namespace Menu
{
  LiquidCrystal_I2C display(0x27, 20, 4);

#define NUM_DRUM_OPTS 5
  HelloDrum *drums[NUM_DRUM_OPTS] = {&snare, &hihat, &crash, &ride};

  int selectedDrum = 0;
  int editing = 0;

  void setup()
  {
    display.init();
    display.backlight();
    display.home();

    display.print("Initializing...");
  }

  void loop()
  {
    }
}