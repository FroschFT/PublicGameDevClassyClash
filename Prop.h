#include "raylib.h"

class Prop
{
// members cannot be accessed (or viewed) from outside the class
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 KnightPos);
    Rectangle GetCollisionRec(Vector2 KnightPos);

// members are accessible from outside the class
private:
    Vector2 WorldPos{}; // world position
    Texture2D Texture{}; // Texture to be Drawn
    float Scale{4.f};

// members cannot be accessed from outside the class, however, they can be accessed in inherited classes.
protected:
};
