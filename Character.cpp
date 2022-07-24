#include "Character.h"
#include "raymath.h"

Character::Character()
{
    width = texture.width/maxFrames;
    height = texture.height;
}


void Character::setScreenPos(int winWidth, int winHeight){
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * width), // getting the rectangle of a single sprite then scale it by 4 because it's tiny
        (float)winHeight / 2.0f - 4.0f * (0.5f * height)
        };
};

void Character::tick(float deltaTime)
{
    worldPosLastFrame = worldPos; //saves the world position before new movement is added

    Vector2 direction{}; // vector to save direction character wants to go
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0; // move left
    if (IsKeyDown(KEY_D))
        direction.x += 1.0; // move right
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0; // move up
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;              // move down
    if (Vector2Length(direction) != 0.0) // check if direction vector is not 0
    {
        // set worldPos = worldPos + direction
        // scales up the normalized vector to match speed
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));

        // check if facing left
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
        texture = idle;

    runningTime += deltaTime;

    // update animation frame
    if (runningTime >= updateTime)
    {
        ++frame;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }
    // Draw knight character
    // rectangle for where to draw knight on screen
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * width, 4.0f * height};
    // rectangle for which knight sprite frame we want
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
};

void Character::undoMovement()
{
   worldPos = worldPosLastFrame;
}