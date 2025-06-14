#include <Arduino.h>
#include "menu.h"
#include "remotes.h"

// Rotary encoder pins
#define CLK 2
#define DT 3
#define BUTTON 4

// how sensitive is the rotary encoder
const int detentSensitivity = 2; 

// Control variables
int shift = 0;
int pulseCounter = 0;
int lastCLKState = 0;
int lastDTState = 0;
bool buttonState = HIGH;
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;


void setup_encoder() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  lastCLKState = digitalRead(CLK);
  lastDTState = digitalRead(DT);
}

enum Rotation {
  NO_ROTATION = 0,
  CLOCKWISE = 1,
  COUNTERCLOCKWISE = -1
};

Rotation rotation_event() {
  /* Detects if the rotary encoder rotated. */
  int currentCLKState = digitalRead(CLK);
  int currentDTState = digitalRead(DT);

  if (currentCLKState == lastCLKState || currentCLKState != LOW) {
    lastCLKState = currentCLKState;
    return NO_ROTATION;
  }

  lastCLKState = currentCLKState;
  return (currentDTState != currentCLKState) ? COUNTERCLOCKWISE : CLOCKWISE;
}

void on_rotation(Rotation rotationEvent){
  /* Handles rotation of the rotary encoder */
  switch (rotationEvent) {
    case CLOCKWISE:
      pulseCounter++;
      break;
    case COUNTERCLOCKWISE:
      pulseCounter--;
      break;
  }
  if (pulseCounter >= detentSensitivity) {
    shift++;
    pulseCounter = 0;
  }
  else if (pulseCounter <= -detentSensitivity) {
    shift--;
    pulseCounter = 0;
  }
  shift = (shift % Menu::menuSize + Menu::menuSize) % Menu::menuSize;
  Menu::show(shift);
}

bool click_event() {
  int reading = digitalRead(BUTTON);

  // Debounce
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        lastButtonState = reading;
        return 1;
      }
    }
  }

  lastButtonState = reading;
  return 0;
}

void on_click(){
  OptionPair selected = Menu::get_selected(shift);
  ButtonRemote::press_button(selected.first);
  IRRemote::press_button(selected.second);
  delay(1000);
  Menu::clear();
}