#ifndef BASE_CHARACTER_H // conditional compilation
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
// members are accessible from outside the class
public:
    BaseCharacter();
    Vector2 GetWorldPos() { return WorldPos; }
    virtual void Tick(float DeltaTime);
    void UnDoMovement();
    Rectangle GetCollisionRec();
    virtual Vector2 GetScreenPos() = 0; // Pure virutal function - not defined on the cpp file - make base character abstract cannot create a instance from it only derive
    bool GetAlive() { return Alive; }
    void SetAlive(bool IsAlive) { Alive = IsAlive; }

    void UnloadTextures();

// members cannot be accessed (or viewed) from outside the class
private:
    bool Alive{true};

// members cannot be accessed from outside the class, however, they can be accessed in inherited classes.
protected:
    // Variables
    Texture2D Idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D Run{LoadTexture("characters/knight_run_spritesheet.png")};
    Texture2D Texture{Idle}; // Texture to be Drawn
    Vector2 WorldPos{};
    // Character facing direction,  1:Facing Right,  -1: Facing Left
    float RightLeft{1.f};
    // Character Animation variables
    const float Scale{4.0}; // character scale
    int MaxFrame{6};
    int Frame{};
    float UpdateTime{1.f/12.f};
    float RunningTime{};
    //speed velocity
    float Speed{4.f};
    // calculate width and height for the frames
    float Width{}; // the width of the character frame
    float Height{}; // the height of the character frame
    // World position on the last frame
    Vector2 WorldPosLastFrame{};
    Vector2 Velocity{};
};
#endif