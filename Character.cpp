#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) : 
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos()
{
    return Vector2
    {
        static_cast<float>(windowWidth) / 2.0f - scale * (width / 2.0f), // getting the rectangle of a single sprite then scale it by 4 because it's tiny
        static_cast<float>(windowHeight) / 2.0f - scale * (height / 2.0f)
    };
}

void Character::tick(float deltaTime)
{

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0; // move left
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0; // move right
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0; // move up
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;  // move down

    BaseCharacter::tick(deltaTime);

};

