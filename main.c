#include "raylib.h"
#include "player.h"
#include "world.h"
#include "camera.h"

int main() {
    // 1. Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Sonic C Exercise");
    Player sonic = Player_Init();
    World world = get_default_world();
    GameCamera gc = Get_GameCamera(&sonic);
    SetTargetFPS(60); 

    
    // 2. The Game Loop
    while (!WindowShouldClose()) {
      Handle_Input(&sonic);
      Update_Physics(&sonic);
      Resolve_Collisions(&sonic, &world);
      Set_Player_State(&sonic);
      Set_Frame(&sonic);
      
      Update_GameCamera(&gc, &sonic);
      BeginDrawing();
        BeginMode2D(gc.camera);
          ClearBackground(BLUE);
          Draw_World(&world);
          Draw_Player(&sonic);
          DrawText("Use Left/Right to move!", 10, 10, 20, DARKGRAY);
        EndMode2D();
      EndDrawing();
    }

    CloseWindow();
    return 0;
}