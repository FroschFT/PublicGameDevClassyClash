#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int WindowWidth{384};
    const int WindowHeight{384};
    InitWindow(WindowWidth, WindowHeight, "Classy Clash");

    // map texture of the game
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 MapPos{0.0, 0.0};
    const float MapScale{4.0};

    // Instanciates the Character class as Knight
    Character Knight{WindowWidth, WindowHeight};

    // Instanciates a Prop from the Prop.h class
    Prop Props[2]{
        Prop {
            Vector2{600.f, 300.f},
            LoadTexture("nature_tileset/Rock.png")
        },
        Prop {
            Vector2{400.f, 500.f},
            LoadTexture("nature_tileset/Log.png")
        }
    };

    // Instanciates the Enemy class as Slime
    Enemy Slime{
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png"),
        Vector2{800.f, 300.f}
    };
    Enemy Rimuru{
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png"),
        Vector2{500.f, 700.f}
    };

    Enemy* enemies[]{
        &Slime,
        &Rimuru
    };

    for (auto enemy : enemies)
    {
        enemy->SetTarget(&Knight);// store the address of the Knight 
    }
    

    SetTargetFPS(60);
    while(!WindowShouldClose()) // clse the window if we click on the x
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // Game condition

        MapPos = Vector2Scale(Knight.GetWorldPos(), -1.f);

        // Draw Map of the game
        DrawTextureEx(map, MapPos, 0.0, MapScale, WHITE);

        // Draw Props on the Map
        for (auto prop : Props)
        {
            prop.Render(Knight.GetWorldPos());
        }

        if (!Knight.GetAlive()) // character is not Alive
        {
            DrawText("Game Over!!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue; // next interation of the loop
        }
        else // character is Alive
        {
            std::string KnightsHealth{"Health: "};
            KnightsHealth.append(std::to_string(Knight.GetHealth()),0, 5);
            DrawText(KnightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }


        // Update Knight comands and animation
        Knight.Tick(GetFrameTime());

        // check map bounds
        if (Knight.GetWorldPos().x < 0.f ||
            Knight.GetWorldPos().y < 0.f ||
            Knight.GetWorldPos().x + WindowWidth > map.width * MapScale ||
            Knight.GetWorldPos().y + WindowHeight > map.height * MapScale
            )
        {
            Knight.UnDoMovement();
        }
        // check prop collisions
        for (auto prop : Props)
        {
            if (CheckCollisionRecs(prop.GetCollisionRec(Knight.GetWorldPos()), Knight.GetCollisionRec()))
            {
                Knight.UnDoMovement();
            }
        }

        // Update enemies animation
        for (auto enemy : enemies)
        {
            enemy->Tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->GetCollisionRec(), Knight.GetWeaponCollisionRec())) // the weapon rec is overlaping the enemy collision rec
                {
                    enemy->SetAlive(false);
                }
            }
        }

        // Game Logic Ends
        EndDrawing();
    }
    UnloadTexture(map);
    Knight.UnloadTextures();
    Slime.UnloadTextures();
    CloseWindow();
}