#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H


void setup_encoder();

enum Rotation {
  NO_ROTATION = 0,
  CLOCKWISE = 1,
  COUNTERCLOCKWISE = -1
};

Rotation rotation_event();
void on_rotation(Rotation rotationEvent);
bool click_event();
void on_click();

#endif