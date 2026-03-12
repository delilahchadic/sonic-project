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