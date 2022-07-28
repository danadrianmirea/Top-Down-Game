#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos; // saves the world position before new movement is added

    runningTime += deltaTime;
    if ( runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if ( frame > maxFrames )
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0) // check if velocity vector is not 0
    {
        // scales up the normalized vector to match speed
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
        texture = idle;

    velocity = {};

    // Draw character
    // rectangle for where to draw on screen
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    // rectangle for which sprite frame we want
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}