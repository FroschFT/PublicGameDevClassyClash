#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Texture2D IdleTexture, Texture2D RunTexture, Vector2 WorldPosi)
{
    Idle = IdleTexture; // cant be initializaed from the initializaed. initialiazed only init variables direct from the class
    Texture = IdleTexture;
    Run = RunTexture;
    WorldPos = WorldPosi;

    Width = Texture.width / MaxFrame;
    Height = Texture.height;

    Speed = 2.5f; // making the enemy a bit slower than the knight
}

void Enemy::Tick(float DeltaTime)
{
    if (!GetAlive()) return;
    Velocity = Vector2Subtract(Target->GetScreenPos(), GetScreenPos());
    if (Vector2Length(Velocity) < Radius) Velocity = {};
    BaseCharacter::Tick(DeltaTime);

    if (CheckCollisionRecs(Target->GetCollisionRec(), GetCollisionRec()))
    {
        Target->TakeDamage(DamagePerSec * DeltaTime);
    }
    
}

Vector2 Enemy::GetScreenPos()
{
    return Vector2Subtract(WorldPos, Target->GetWorldPos());
}
