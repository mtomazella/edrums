#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Drum.hpp"
#include "drumsSetup.hpp"
#include "RotaryEncoder.h"

LiquidCrystal_I2C display(0x27, 20, 4);

#define ENCODER_PIN_CLK 15
#define ENCODER_PIN_DT 2
#define ENCODER_PIN_SW 4
RotaryEncoder encoder(ENCODER_PIN_DT, ENCODER_PIN_CLK);

enum MenuDepth
{
  selectingDrum,
  selectingOption,
  editingOption
};

enum DrumTab
{
  none,
  note,
  sensitivity,
  threshold,
  curveType,
  masktime,
  scantime
};

enum ButtonAction
{
  noAction,
  pressed,
  longPressed
};

class Menu
{
private:
  unsigned short currentDrum = 0;
  MenuDepth menuDepth = MenuDepth::selectingDrum;
  DrumTab currentEditingTab = DrumTab::note;

  bool requestDisplay = true;
  int lastEncoderPosition = 0;

public:
  void init()
  {
    display.init();
    display.backlight();
    display.home();

    display.print("Initializing...");

    pinMode(ENCODER_PIN_SW, INPUT_PULLUP);
  }

  int getClampedEncoderPosition(int position, int min, int max, bool loopBack = true, bool loopFront = true)
  {
    int newEncoderPosition = position;
    if (newEncoderPosition > max)
    {
      newEncoderPosition = loopFront ? newEncoderPosition - max : max;
      encoder.setPosition(newEncoderPosition);
    }
    if (newEncoderPosition < min)
    {
      newEncoderPosition = loopBack ? max + newEncoderPosition + 1 : min;
      encoder.setPosition(newEncoderPosition);
    }
    return newEncoderPosition;
  }

  ButtonAction getButtonAction()
  {
    static unsigned long lastPress = 0;
    static unsigned long lastRelease = 0;
    bool buttonBeingPressed = digitalRead(ENCODER_PIN_SW) == LOW;
    unsigned long time = millis();

    if (buttonBeingPressed && lastRelease >= lastPress && time - lastRelease >= 100)
      lastPress = time;
    else if (!buttonBeingPressed && lastPress > lastRelease)
    {
      lastRelease = time;
      if (time - lastPress > 1000)
        return ButtonAction::pressed;
      else
        return ButtonAction::longPressed;
    }
    return ButtonAction::noAction;
  }

  void inputLoop()
  {
    encoder.tick();

    int encoderPosition = encoder.getPosition();
    if (encoderPosition == lastEncoderPosition)
      return;
    requestDisplay = true;
    lastEncoderPosition = encoderPosition;

    ButtonAction buttonAction = getButtonAction();

    if (menuDepth == MenuDepth::selectingDrum)
    {
      encoderPosition = getClampedEncoderPosition(encoderPosition, 0, NUM_DRUMS + NUM_PEDALS - 1);
      currentDrum = encoderPosition;

      if (buttonAction == ButtonAction::pressed)
        menuDepth = MenuDepth::selectingOption;
    }
  }

  template <typename DrumT>
  void displayDrum(EDrum<DrumT> *drum)
  {
    display.clear();
    display.home();
    display.printf("%s", drum->name.c_str());
  }

  template <typename DrumT>
  void displayOption(EDrum<DrumT> *drum, bool displayValue)
  {
    display.setCursor(0, 1);
    switch (currentEditingTab)
    {
    case DrumTab::note:
      display.printf("Note %d", drum->note);
      break;
    }
  }

  void displayLoop()
  {
    if (currentDrum < NUM_DRUMS)
    {
      displayDrum<HelloDrum>(DRUMS[currentDrum]);
      displayOption<HelloDrum>(DRUMS[currentDrum], true);
    }
    else
    {
      displayDrum<Pedal>(PEDALS[currentDrum - NUM_DRUMS]);
      displayOption<Pedal>(PEDALS[currentDrum - NUM_DRUMS], true);
    }
  }

  void
  loop()
  {
    inputLoop();

    if (requestDisplay)
    {
      requestDisplay = false;
      displayLoop();
    }
  }
};