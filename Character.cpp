#include "Character.h"
#include "raymath.h"

Character::Character(int WindowWidth, int WindowHeight) :
    WindowWidth(WindowWidth),
    WindowHeight(WindowHeight)
{
    Width = Texture.width / MaxFrame;
    Height = Texture.height;
}

Vector2 Character::GetScreenPos()
{
    return Vector2{
        static_cast<float>(WindowWidth)/2.0f - (0.5f * Width) * Scale,
        static_cast<float>(WindowHeight)/2.0f - (0.5f * Height) * Scale
    };
}

void Character::Tick(float DeltaTime)
{
    if (!GetAlive()) return;
    // Define the movement of the map
    if (IsKeyDown(KEY_A)) {Velocity.x -= 1.0;}
    if (IsKeyDown(KEY_D)) Velocity.x += 1.0;   // if the "if" statement only have one line we can omit the curly braces
    if (IsKeyDown(KEY_W)) {Velocity.y -= 1.0;}
    if (IsKeyDown(KEY_S)) {Velocity.y += 1.0;}
    // update velocity than tick
    BaseCharacter::Tick(DeltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (RightLeft > 0.f)
    {
        origin = {0.f, Weapon.height * Scale};
        offset = {35.f, 55.f};
        WeaponCollisionRec = {
            GetScreenPos().x + offset.x,
            GetScreenPos().y + offset.y - Weapon.height * Scale,
            Weapon.width * Scale,
            Weapon.height * Scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
    }
    else
    {
        origin = {Weapon.width * Scale, Weapon.height * Scale};
        offset = {25.f, 55.f};
        WeaponCollisionRec = {
            GetScreenPos().x + offset.x - Weapon.width * Scale,
            GetScreenPos().y + offset.y - Weapon.height * Scale,
            Weapon.width * Scale,
            Weapon.height * Scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
    }

    // draw the sword
    Rectangle Source{
        0.f,
        0.f,
        static_cast<float>(Weapon.width) * RightLeft,
        static_cast<float>(Weapon.height)};
    Rectangle Destination{
        GetScreenPos().x + offset.x,
        GetScreenPos().y + offset.y,
        Weapon.width * Scale,
        Weapon.height * Scale};
    DrawTexturePro(Weapon, Source, Destination, origin, rotation, WHITE);

    // DrawRectangleLines(
    //     WeaponCollisionRec.x,
    //     WeaponCollisionRec.y,
    //     WeaponCollisionRec.width,
    //     WeaponCollisionRec.height,
    //     RED
    // );
}


void Character::TakeDamage(float Damage)
{
    Health -= Damage;
    if (Health <= 0.f)
    {
        SetAlive(false);
    }
    
}