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

enum class MenuDepth
{
  selectingDrum,
  selectingOption,
  editingOption
};

enum class DrumTab
{
  none,
  note,
  sensitivity,
  threshold,
  curveType,
  masktime,
  scantime,
  fixVelocity
};
short tabCount = 8;

enum class ButtonAction
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

  template <typename DrumT>
  int getOptionValue(EDrum<DrumT> *drum, DrumTab option)
  {
    switch (currentEditingTab)
    {
    case DrumTab::note:
      return drum->note;
      break;
    case DrumTab::sensitivity:
      return drum->sensitivity;
      break;
    case DrumTab::threshold:
      return drum->threshold;
      break;
    case DrumTab::curveType:
      return drum->curveType;
      break;
    case DrumTab::masktime:
      return drum->masktime;
      break;
    case DrumTab::scantime:
      return drum->scantime;
      break;
    case DrumTab::fixVelocity:
      return drum->fixedVelocity;
      break;
    }
    return 0;
  }

  template <typename DrumT>
  void setOptionValue(EDrum<DrumT> *drum, DrumTab option, byte value)
  {
    switch (currentEditingTab)
    {
    case DrumTab::note:
      drum->note = value;
      break;
    case DrumTab::sensitivity:
      drum->sensitivity = value;
      break;
    case DrumTab::threshold:
      drum->threshold = value;
      break;
    case DrumTab::curveType:
      drum->curveType = value;
      break;
    case DrumTab::masktime:
      drum->masktime = value;
      break;
    case DrumTab::scantime:
      drum->scantime = value;
      break;
    case DrumTab::fixVelocity:
      drum->fixedVelocity = value;
      break;
    }
  }

  ButtonAction getButtonAction()
  {
    static unsigned long lastPress = 0;
    static unsigned long lastRelease = 0;
    bool buttonBeingPressed = digitalRead(ENCODER_PIN_SW) == LOW;
    unsigned long time = millis();

    if (buttonBeingPressed && lastRelease >= lastPress)
      lastPress = time;
    else if (!buttonBeingPressed && lastPress > lastRelease)
    {
      lastRelease = time;

      if (time - lastPress < 100)
        return ButtonAction::noAction;
      if (lastRelease - lastPress > 300)
        return ButtonAction::longPressed;
      return ButtonAction::pressed;
    }

    return ButtonAction::noAction;
  }

  void inputLoop()
  {
    encoder.tick();
    ButtonAction buttonAction = getButtonAction();

    int encoderPosition = encoder.getPosition();
    if (encoderPosition == lastEncoderPosition && buttonAction == ButtonAction::noAction)
      return;
    requestDisplay = true;
    lastEncoderPosition = encoderPosition;

    if (menuDepth == MenuDepth::selectingDrum)
    {
      encoderPosition = getClampedEncoderPosition(encoderPosition, 0, NUM_DRUMS + NUM_PEDALS - 1);
      currentDrum = encoderPosition;

      if (buttonAction == ButtonAction::pressed)
      {
        menuDepth = MenuDepth::selectingOption;
        encoder.setPosition(0);
      }
    }
    else if (menuDepth == MenuDepth::selectingOption)
    {
      encoderPosition = getClampedEncoderPosition(encoderPosition, 1, tabCount - 1);
      currentEditingTab = (DrumTab)encoderPosition;

      if (buttonAction == ButtonAction::longPressed)
      {
        menuDepth = MenuDepth::selectingDrum;
        encoder.setPosition(currentDrum);
      }
      else if (buttonAction == ButtonAction::pressed)
      {
        menuDepth = MenuDepth::editingOption;
        encoder.setPosition(
            currentDrum < NUM_DRUMS
                ? getOptionValue<HelloDrum>(DRUMS[currentDrum], currentEditingTab)
                : getOptionValue<Pedal>(PEDALS[currentDrum - NUM_DRUMS], currentEditingTab));
      }
    }
    else if (menuDepth == MenuDepth::editingOption)
    {
      int min = 1, max = 100;
      if (currentEditingTab == DrumTab::curveType)
      {
        min = 0;
        max = 4;
      }
      else if (currentEditingTab == DrumTab::fixVelocity || currentEditingTab == DrumTab::note)
      {
        min = 0;
        max = 127;
      }

      encoderPosition = getClampedEncoderPosition(encoderPosition, min, max);
      if (currentDrum < NUM_DRUMS)
        setOptionValue<HelloDrum>(DRUMS[currentDrum], currentEditingTab, encoderPosition);
      else
        setOptionValue<Pedal>(PEDALS[currentDrum - NUM_DRUMS], currentEditingTab, encoderPosition);

      if (buttonAction == ButtonAction::longPressed)
      {
        menuDepth = MenuDepth::selectingDrum;
        encoder.setPosition(currentDrum);
      }
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
    case DrumTab::sensitivity:
      display.printf("Sensitivity %d", drum->sensitivity);
      break;
    case DrumTab::threshold:
      display.printf("Threshold %d", drum->threshold);
      break;
    case DrumTab::curveType:
      display.printf("Curve %d", drum->curveType);
      break;
    case DrumTab::masktime:
      display.printf("Masktime %d", drum->masktime);
      break;
    case DrumTab::scantime:
      display.printf("Scantime %d", drum->scantime);
      break;
    case DrumTab::fixVelocity:
      display.printf("F. Velocity %d", drum->fixedVelocity);
      break;
    }
  }

  void displayLoop()
  {
    if (currentDrum < NUM_DRUMS)
    {
      displayDrum<HelloDrum>(DRUMS[currentDrum]);
      if (menuDepth != MenuDepth::selectingDrum)
        displayOption<HelloDrum>(DRUMS[currentDrum], true);
    }
    else
    {
      displayDrum<Pedal>(PEDALS[currentDrum - NUM_DRUMS]);
      if (menuDepth != MenuDepth::selectingDrum)
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