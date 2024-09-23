#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) :
    WorldPos(pos),
    Texture(tex)
{
    
}

void Prop::Render(Vector2 KnightPos)
{
    Vector2 ScreenPos{ Vector2Subtract(WorldPos, KnightPos) };
    DrawTextureEx(Texture, ScreenPos, 0.f, Scale, WHITE);
}

Rectangle Prop::GetCollisionRec(Vector2 KnightPos)
{
    Vector2 ScreenPos{ Vector2Subtract(WorldPos, KnightPos) };
    return Rectangle{
        ScreenPos.x,
        ScreenPos.y,
        Texture.width * Scale,
        Texture.height * Scale
    };
}