#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Texture2D idle;
    Texture2D run;
    Vector2 screenPos;
    Vector2 worldPos;
    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    // animation varialbes
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};
    const float speed{4.f};
};

void Character::setScreenPos(int winWidth, int winHeight){
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6), // getting the rectangle of a single sprite then scale it by 4 because it's tiny
        (float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)}};

void Character::tick(float deltaTime)
{
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
};

int main()
{
    // Setting variables for the popup window dimensions
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Top Down Game");

    // set up of fps for running the game
    int fps{60};
    SetTargetFPS(fps);

    // background variable which gets the background png drawing
    Texture2D background = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 backpos{0.0, 0.0}; // background x and y position relative to window
    float backrot{0.0};        // background rotation
    float backscale{4.0};      // background scale
    float speed{4.0};

    // knight variables

    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");

    Vector2 knightPos{
        (float)windowWidth / 2.0f - 4.0f * (0.5f * (float)knight.width / 6), // getting the rectangle of a single sprite then scale it by 4 because it's tiny
        (float)windowHeight / 2.0f - 4.0f * (0.5f * (float)knight.height)};
    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};

    // animation varialbes
    float runningTime{};
    int knightFrame{0};
    const int maxKnightFrames{6};
    const float updateTime{1.f / 12.f};

    // origin is the anchor where you rotate or scale a vector
    Vector2 origin{0.0, 0.0};

    while (!WindowShouldClose())
    {
        // start drawing which will be a popup window
        BeginDrawing();
        ClearBackground(WHITE);

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
            // set backpos = backpos - direction
            // scales up the normalized vector to match speed
            backpos = Vector2Subtract(backpos, Vector2Scale(Vector2Normalize(direction), speed));

            // check if facing left
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            knight = knight_run;
        }
        else
            knight = knight_idle;

        // draw the background to the game, takes input of the spritesheet, position, rotation and scale
        DrawTextureEx(background, backpos, backrot, backscale, WHITE);

        // update animation frame
        runningTime += GetFrameTime();

        if (runningTime >= updateTime)
        {
            ++knightFrame;
            runningTime = 0.f;
            if (knightFrame > maxKnightFrames)
                knightFrame = 0;
        }

        // Draw knight character
        // rectangle for where to draw knight on screen
        Rectangle knightDest{knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.0f, 4.0f * (float)knight.height};
        // rectangle for which knight sprite frame we want
        Rectangle knightSource{(float)knightFrame * knight.width / 6.f, 0.f, rightLeft * (float)knight.width / 6.f, (float)knight.height};
        DrawTexturePro(knight, knightSource, knightDest, origin, 0, WHITE);

        // stop drawing (graphics)
        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(knight);

    CloseWindow();

    return 0;
}