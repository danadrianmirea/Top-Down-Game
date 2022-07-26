#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main()
{
    // Setting variables for the popup window dimensions
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Top Down Game");

    // set up of fps for running the game
    const int fps{60};
    SetTargetFPS(fps);

    // map variable which gets the background png drawing
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0}; // map x and y position relative to window
    const float mapRot{0.0};        // map rotation
    const float mapScale{4.0};      // map scale

    //set up a character call knight and use class function to place it in the center of the screen
    Character knight(windowWidth, windowHeight);  
    Enemy goblin(Vector2{}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png") );  

    //array to store props to be used on map
    Prop props[2]{
        {Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        {Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
    };


    while (!WindowShouldClose())
    {
        // start drawing which will be a popup window
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the background to the game, takes input of the spritesheet, position, rotation and scale
        DrawTextureEx(map, mapPos, mapRot, mapScale, WHITE);

                //renders each prop to display on screen
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }


        //use tick class function to update knight animation and draw the sprite on the screen
        knight.tick(GetFrameTime());

        //checking map bounds 
        if (knight.getWorldPos().x < 0.f || 
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale )
        {
            knight.undoMovement();
        }

        //checking collisions with props
        for(auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        goblin.tick(GetFrameTime());

        // stop drawing (graphics)
        EndDrawing();
    }

    CloseWindow();

    return 0;
}