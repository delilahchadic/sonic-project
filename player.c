#include "player.h"
Player Player_Init(){
  Player player = { 0 };
  player.position = (Vector2){ 100,340 }; // Start in middle
  player.speed = 0.05f;
  player.gravity = 0.5f;
  player.isGrounded = true;
  player.sprite = Get_Default_Sonic();
  player.frame = 0;
  player.deceleration = 0.5f;
  player.frameTimer = 0.0f;
  player.skidTimer = 0.0f;
  player.state = idle;
  player.maxSpeed = 6.0f;
  player.lookingRight = true;
  return player;
}

//handles move left, right and jump buttons
void Handle_Input(Player* player){
  if (IsKeyPressed(KEY_SPACE) && player->isGrounded) {
    player->velocity.y -= 12.0f;
    player->isGrounded = false;
    player->state = jumping;
  }

  if(IsKeyReleased(KEY_SPACE) && !player->isGrounded){
    if(player->velocity.y < -4.0){
      player->velocity.y = -4.0f;
    } 
  }

  // if(IsKeyDown(KEY_S)){
  //   if(fabsf(player->velocity.x) > 0.5f){
  //     player->state = rolling;
  //   }
  // }
  if(player->state != rolling && player->state != crouching){
    if (IsKeyDown(KEY_D)){
    if(player->velocity.x <0){
      player->velocity.x += player->deceleration;
    }else if(fabsf(player->velocity.x) < player->maxSpeed){
      player->velocity.x += player->speed;
    }
    if(player->state != skidding && player->velocity.x > 0){
      player->lookingRight = true;
    }
    
  }
   
  if (IsKeyDown(KEY_A)) {
    if(player->velocity.x > 0){
      player->velocity.x -= player->deceleration;
    } else if(fabsf(player->velocity.x) < player->maxSpeed){
      player->velocity.x -= player->speed;
    }
    if(player->state != skidding && player->velocity.x < 0){
      player->lookingRight = false;
    }
  }
  }
  
}

//applies gravity then friction and then where sonic should be given his x and y velocity
void Update_Physics(Player* player){ 
  if(!player->isGrounded){
    player->velocity.y += player->gravity;
  }
  if(player->velocity.x < 0){
    player->velocity.x += 0.016875f; 
  } else if (player->velocity.x > 0){
    player->velocity.x -= 0.016875f; 
  }
  player->position.x += player->velocity.x;
  player->position.y += player->velocity.y;
  
}

//Checks to see if sonic is on the ground or not
void Resolve_Collisions(Player* player, World* world){
  //determines what block sonic is on.... maybe could be moved to world?
  int cellX = (int)(player->position.x / world->tileSize);
  int cellY = (int)((player->position.y + 20) / world->tileSize);

  // 1. Check if we are inside the array boundaries
  if (cellX >= 0 && cellX < world->columns && cellY >= 0 && cellY < world->rows) {
      
      // 2. Is the tile solid?
      if (World_GetTile(world, cellX, cellY) == 1) {
          
          // 3. Only 'Land' if we are falling DOWN
          if (player->velocity.y >= 0) {
              player->position.y = (cellY * world->tileSize) - 20; // Snap feet to top of tile
              player->velocity.y = 0;
              player->isGrounded = true;
              // player->state =idle;
              Set_Player_State(player);
          }
      } else {
          player->isGrounded = false;
      }
  }
}

//called after take input and apply physics uses sonics state and speed and is grounded
//to determine nex state
void Set_Player_State(Player* player){
  if(!player->isGrounded){
    return;
  }
  if(player->skidTimer >0.0f){
    player->skidTimer -= GetFrameTime();
    return;
  }
  float speed = fabsf(player->velocity.x);
  
  if(IsKeyDown(KEY_S)){
    if(speed > 1.0){
      player->state = rolling;
      return;
    } else{
      player->state = crouching;
      return;
    }
  }
  
  if(speed >2.0){
    
    bool pressingLeft = IsKeyDown(KEY_A);
    bool pressingRight = IsKeyDown(KEY_D);
    if(pressingRight && player->velocity.x <0){
      player->state = skidding;
      player->lookingRight = false;
      player->skidTimer = 0.5f;
      return;
    } else if(pressingLeft && player->velocity.x >0){
      player->state = skidding;
      player->lookingRight = true;
      player->skidTimer = 0.5f;
      return;
    }
    player->state =running;
  } else if(speed > 0.2f){
    player->state = walking;
  } else{
    player->state = idle;
  }
}

//this sets the characters frame for animation based on state and where it is in the animation
void Set_Frame(Player* player){
  if(player->state==idle){
    player->frame = 0;
    player->frameTimer = 0;
    return;
  } 
  float speed = fabsf(player->velocity.x);
  AnimationRange range = Get_Animation_Range(player);
  
  if(player->frame < range.start_frame || player->frame >= range.end_frame){
    player ->frame = range.start_frame;
    player->frameTimer = 0;
  }

  float animation_duration = 0.1f -(0.01f * speed) ;
  player->frameTimer += GetFrameTime();
  if(player->frameTimer > animation_duration){
    player->frame++;
    player->frameTimer = 0;
  }
  return;
}

// grabs the correct indices for the expected sprite ranges
AnimationRange Get_Animation_Range(Player* player){
  switch (player->state)
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

// determines where and what to draw and draws current player
void Draw_Player(Player* player){
  Vector2 position = { 
    player->position.x - (24 / 2.0f), 
    player->position.y - (33 / 2.0f) 
  };

  Rectangle r = Get_Current_Animation(player);
  DrawTextureRec(player->sprite.texture,r,position,WHITE);
}

/// @brief - returns the current animation by checking the state and rudimentary deciding if facing left or not
/// @param player 
/// @return Rectangle containing the correct current sprite of sonic
Rectangle Get_Current_Animation(Player* player){
  switch (player->state)
  {
  case idle:
    return Get_Sonic_Standby(player->lookingRight);
  case walking:
    return Get_Sonic_Walking(player->frame,player->lookingRight);
  case running:
    return Get_Sonic_Running(player->frame,player->lookingRight);
  case jumping:
    return Get_Sonic_Jumping(player->frame);
  case skidding:
    return Get_Sonic_Skidding(player->lookingRight);
  case rolling:
    return Get_Sonic_Jumping(player->frame);
  case crouching:
    return Get_Sonic_Crouching(player->lookingRight);
  default:
    return (Rectangle){0};
  }
}

