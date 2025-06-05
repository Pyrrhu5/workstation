#include <Arduino.h>
#include "menu.h"

// Rotary encoder pins
#define CLK 2
#define DT 3

// how sensitive is the rotary encoder
const int detentSensitivity = 2; 

// Control variables
int shift = 0;
int pulseCounter = 0;
int lastCLKState = 0;
int lastDTState = 0;

// TODO You have nothing to do here, you should come from menu.cpp
// but the fucker get only 0 as value
const int menuSize = 5; //sizeof(menuOptions) / sizeof(menuOptions[0]);

void setup_encoder() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
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
  shift = (shift % menuSize + menuSize) % menuSize;
  show_menu(shift);
}
