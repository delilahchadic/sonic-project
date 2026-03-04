#include "camera.h"

GameCamera Get_GameCamera(Player* player){
  GameCamera gc = {0};
  gc.camera.target = player -> position;
  gc.camera.offset = (Vector2) { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
  gc.camera.rotation = 0.0f;
  gc.camera.zoom = 1.0f;
  gc.lerpSpeed = 0.05f;
  gc.zoom = 1.0f;

  return gc;
}
void Update_GameCamera(GameCamera* gc, Player* player){
  float lerpSpeed = 0.05f; // Adjust this: 1.0 is "Locked", 0.05 is "Lazy"
  gc->camera.target.x += (player->position.x - gc->camera.target.x) * lerpSpeed;
  gc->camera.target.y += (player->position.y - gc->camera.target.y) * lerpSpeed;
  gc->camera.zoom += (gc->zoom - gc->camera.zoom) * 0.1f;
}