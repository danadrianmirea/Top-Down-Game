#include "raylib.h"


int main()
{
    //Setting variables for the popup window dimensions
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Top Down Game");

    //set up of fps for running the game
    int fps{60};
    SetTargetFPS(fps);

    //background variable which gets the background png drawing
    Texture2D background = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 backpos {0.0, 0.0}; //background x and y position relative to window
    float backrot{0.0}; //background rotation
    float backscale{4.0}; //background scale 

    while (!WindowShouldClose())
    {
        //start drawing which will be a popup window
        BeginDrawing();
        ClearBackground(WHITE);

        //draw the background to the game, takes input of the spritesheet, position, rotation and scale
        DrawTextureEx(background, backpos, backrot,  backscale, WHITE);
        
        //stop drawing (graphics)
        EndDrawing();
    }

    UnloadTexture(background);

    CloseWindow();

    return 0;
}