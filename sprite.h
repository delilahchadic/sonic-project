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

Rectangle Get_Sonic_Running(int frame, bool lookingRight);
Rectangle Get_Sonic_Walking(int frame, bool lookingRight);  // returns the correct running sprite and 0 for default
Rectangle Get_Sonic_Jumping(int frame);
Rectangle Get_Sonic_Standby(bool lookingRight);
Rectangle Get_Sonic_Skidding(bool lookingRight);
Rectangle Get_Sonic_Crouching(bool lookingRight);
#endif