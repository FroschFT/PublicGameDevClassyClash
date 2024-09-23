#ifndef CHARACTER_H // conditional compilation
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
// members are accessible from outside the class
public:
    Character(int WindowWidth, int WindowHeight);
    virtual void Tick(float DeltaTime) override;
    virtual Vector2 GetScreenPos() override;
    Rectangle GetWeaponCollisionRec() { return WeaponCollisionRec; }
    float GetHealth() const { return Health; } // allocating const is making a promise to never change any members
    void TakeDamage(float Damage);

// members cannot be accessed (or viewed) from outside the class
private:
    int WindowWidth{};
    int WindowHeight{};
    Texture2D Weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle WeaponCollisionRec{};
    float Health{100.f};

// members cannot be accessed from outside the class, however, they can be accessed in inherited classes.
protected:
};
#endif