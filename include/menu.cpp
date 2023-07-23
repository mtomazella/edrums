#include <Wire.h>
#include <LiquidCrystal_I2C.h>

namespace Menu
{
  LiquidCrystal_I2C display(0x27, 20, 4);

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