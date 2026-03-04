#ifndef CAMERA_H
#define CAMERA_H
#include "raylib.h"
#include "player.h"
typedef struct{
  Camera2D camera;
  float lerpSpeed;
  float zoom;
} GameCamera;

GameCamera Get_GameCamera(Player* player);
void Update_GameCamera(GameCamera* gc, Player* player);
#endif