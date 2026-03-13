#include "sprite.h"
#include <stdio.h>

//provides a default Sprite struct
// loads the sprites file and 
// returns a sprite object to manage the texture file
// functions in here 
Sprite Get_Default_Sonic(){
  Sprite sonic = {0};
  sonic.file_name = "sprites.png";
  Image image = LoadImage(sonic.file_name);
  Color skyBlue = { 148, 189, 237, 255 }; 
  ImageColorReplace(&image, skyBlue, BLANK);
  sonic.texture = LoadTextureFromImage(image);
  UnloadImage(image);
  return sonic;
}

/// @brief Get_Sonic_Standby
/// @param lookingRight which direction sonic should be looking
/// @return the rectangle from when sonic is not moving
Rectangle Get_Sonic_Standby(bool lookingRight){

  float width = lookingRight? 24.0: -24.0;//runningLeft? 24.0: -24.0;
  float height = 32.0f;
  Rectangle r = {151,1,width,height};
    return r;
}

Rectangle Get_Sonic_Skidding(bool lookingRight){
  float width = lookingRight? 24.0: -24.0;
  float height = 32.0f;
  Rectangle r = {151,height+2,width,height};
    return r;
}

Rectangle Get_Sonic_Walking(int frame, bool lookingRight){
  float width = lookingRight? 24.0: -24.0;
  int height = 32;
  int temp_index = frame - 1;
  int tl_pixel =((fabsf(width)+1) * temp_index)+1;
  Rectangle r = {tl_pixel, 1, width,height};
  return r;
}

Rectangle Get_Sonic_Running(int frame, bool lookingRight){
  float width = lookingRight? 24.0: -24.0;
  int height = 32;
  int temp_index = frame - 6;
  int tl = temp_index *(fabsf(width)+1)+1;
  Rectangle r = {tl, height+2, width,height};
  return r;
}

Rectangle Get_Sonic_Jumping(int frame){
  float width = 24.0f;
  int tl_pixel = 201;

  int temp_index = frame - 10;
  int index_width = temp_index * (width+1);
  Rectangle r = {tl_pixel + index_width, 1, width-2,width-2};
  return r;
}

Rectangle Get_Sonic_Crouching(bool lookingRight){
  float width = lookingRight? 24.0f : -24.0f;
  int tl_pixel = 176;

  Rectangle r = {tl_pixel, 1, width,fabsf(width)};
  return r;
}

/// @brief - returns the current animation by checking the state and rudimentary deciding if facing left or not
/// @param player 
/// @return Rectangle containing the correct current sprite of sonic
Rectangle Get_Current_Animation(PlayerState state, int frame, bool lookingRight){
  switch (state)
  {
  case idle:
    return Get_Sonic_Standby(lookingRight);
  case walking:
    return Get_Sonic_Walking(frame,lookingRight);
  case running:
    return Get_Sonic_Running(frame,lookingRight);
  case jumping:
    return Get_Sonic_Jumping(frame);
  case skidding:
    return Get_Sonic_Skidding(lookingRight);
  case rolling:
    return Get_Sonic_Jumping(frame);
  case crouching:
    return Get_Sonic_Crouching(lookingRight);
  default:
    return (Rectangle){0};
  }
}

// grabs the correct indices for the expected sprite ranges
AnimationRange Get_Animation_Range(PlayerState state){
  switch (state)
  {
  case walking:
    return (AnimationRange){1,5};
  case running:
    return (AnimationRange){6,9};
  case jumping:
    return (AnimationRange){10,14};
  case rolling:
    return (AnimationRange){10,14};
  default:
    return(AnimationRange) {0,0};
  }
}