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
        screenPos.x,
        screenPos.y,
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

    // Draw character
    // rectangle for where to draw on screen
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
    // rectangle for which sprite frame we want
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}