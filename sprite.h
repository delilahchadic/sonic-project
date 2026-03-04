#ifndef SPRITE_H
#define SPRITE_H
#include <stddef.h>  //
#include <math.h>
#include "raylib.h"
typedef struct{
  char* file_name;
  // Image image;
  Texture2D texture;
} Sprite;

Sprite Get_Default_Sonic();

Rectangle Get_Sonic_Running(int frame, bool runningLeft);
Rectangle Get_Sonic_Walking(int frame, bool runningLeft);  // returns the correct running sprite and 0 for default
Rectangle Get_Sonic_Jumping(int frame);
Rectangle Get_Sonic_Standby();
#endif