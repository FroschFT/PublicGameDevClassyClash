#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public: // members are accessible from outside the class
    Enemy(Texture2D IdleTexture, Texture2D RunTexture, Vector2 WorldPosi);
    virtual void Tick(float DeltaTime) override;
    void SetTarget( Character*  character) { Target = character; }
    virtual Vector2 GetScreenPos() override;

private: // members cannot be accessed (or viewed) from outside the class
    Character* Target; // to store the address of a variable type Character heres a pointer variable named Target
    float DamagePerSec{10.f}; // if the enemy is ovelaping with the caracter take damage
    float Radius{25.f};

protected: // members cannot be accessed from outside the class, however, they can be accessed in inherited classes.
};