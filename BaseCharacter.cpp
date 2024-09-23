#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{}

void BaseCharacter::Tick(float DeltaTime)
{
    WorldPosLastFrame = WorldPos;

    // Update animation frame
    RunningTime += GetFrameTime();
    if (RunningTime >= UpdateTime)
    {
        Frame++;
        RunningTime = 0.f;
        if (Frame > MaxFrame) { Frame = 0; }
    }

    // Define the movement of the map
    if (Vector2Length(Velocity) != 0.0)
    {
        // set WorldPos = WorldPos + Direction
        WorldPos = Vector2Add(WorldPos, Vector2Scale(Vector2Normalize(Velocity), Speed));
        Velocity.x < 0.f ? RightLeft = -1.f : RightLeft = 1.f;
        Texture = Run; // Texture state is running
    }
    else
    {
        Texture = Idle; // Texture state is idle
    }
    Velocity = {}; // zeroing out the velocity after it move

    // Draw BaseCharacter on the game
    Rectangle Source{ // Source/Origin where the BaseCharacter is actually
        Width * Frame,
        0.f,
        Width * RightLeft,
        Height
    };
    Rectangle Destination{ // Destination where the BaseCharacter is gonna be
        GetScreenPos().x,
        GetScreenPos().y,
        Width * Scale,
        Height * Scale
    };
    DrawTexturePro(Texture, Source, Destination, Vector2{}, 0.f, WHITE);
}

void BaseCharacter::UnDoMovement()
{
    WorldPos = WorldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        GetScreenPos().x,
        GetScreenPos().y,
        Width * Scale,
        Height * Scale
    };
}

void BaseCharacter::UnloadTextures()
{
    UnloadTexture(Texture);
    UnloadTexture(Run);
    UnloadTexture(Idle);
}