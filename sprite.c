#include "sprite.h"
#include <stdio.h>
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

Rectangle Get_Sonic_Standby(){
  float width = 24.0f;//runningLeft? 24.0: -24.0;
  float height = 32.0f;
  Rectangle r = {151,1,width,height};
    return r;
}
Rectangle Get_Sonic_Walking(int frame, bool runningLeft){
  // if(frame < 1){
  //   frame = 1;
  // }
  float width = runningLeft? 24.0: -24.0;
  int height = 32;
  int temp_index = frame - 1;
  int tl_pixel =((fabsf(width)+1) * temp_index)+1;
  Rectangle r = {tl_pixel, 1, width,height};
  return r;
}

Rectangle Get_Sonic_Running(int frame, bool runningLeft){
  // if(frame < 6){
  //   frame = 6;
  // }
  float width = runningLeft? 24.0: -24.0;
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
