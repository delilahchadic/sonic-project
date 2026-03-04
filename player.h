#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "world.h"
#include "sprite.h"
#include <math.h>

typedef enum{
  idle,
  walking,
  running,
  jumping,
  crouching,
  rolling
} PlayerState;

typedef struct {
  int start_frame;
  int end_frame;
} AnimationRange;

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Sprite sprite;
    float speed;
    float gravity;
    bool isGrounded;
    int frame;
    float frameTimer;
    PlayerState state;
} Player;

Player Player_Init();

void Handle_Input(Player* player);
void Update_Physics(Player* player);
void Resolve_Collisions(Player* player, World* world);
void Set_Player_State(Player* player);
void Set_Frame(Player* player);
Rectangle Get_Current_Animation(Player* player);
AnimationRange Get_Animation_Range(Player* player);


void Draw_Player(Player* player);


#endif