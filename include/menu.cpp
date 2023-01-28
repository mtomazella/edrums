#include <Wire.h>
#include <LiquidCrystal_I2C.h>

namespace Menu
{
  LiquidCrystal_I2C display(0x27, 20, 4);

  void setup()
  {
    display.init(); // initialize the lcd
    display.backlight();
    display.home();

    display.print("Hello world...");
  }

  void loop()
  {
  }
}