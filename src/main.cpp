#include <iostream>
#include <vector>
#include <utility>
#include <raylib/raylib.h>

#include "tileset.hpp"
#include "tilemap.hpp"
#include "wfc.hpp"
#include "tileutils.hpp"
#include "rule_parser.hpp"
//#include "isotilemap.hpp"

#define WIDTH 1366
#define HEIGHT 1366

struct InputData {
    char *image;
    Vector2 tileSize;
    int xTiles;
    int yTiles;
    char *rules;
};

InputData pipeData = {
    "tilemaps/pipes/tilemap.png",
    {10, 10},
    5,
    4,
    "tilemaps/pipes/rules.json"
};

InputData battleData = {
    "tilemaps/tiny_battle/tilemap_packed.png",
    {16, 16},
    18,
    11,
    "tilemaps/tiny_battle/rules.json"
};

InputData circleData = {
    "tilemaps/circles/tilemap.png",
    {32, 32},
    8,
    4,
    "tilemaps/circles/rules.json"
};

InputData townData = {
    "tilemaps/sketch-town/tilemap.png",
    {256, 352},
    8,
    2,
    "tilemaps/sketch-town/rules.json"
};

InputData cityData = {
    "tilemaps/city/tilemap.png",
    {133, 133},
    5,
    25,
    "tilemaps/city/rules.json"
};

 
int main() {
    InitWindow(WIDTH, HEIGHT, "Wave Function Collapse");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    InputData data = pipeData;
    RuleParser parser(data.rules);

    int scale = 1;
    
    Camera2D camera = { 0 };
    float cameraSpeed = 10;
    camera.zoom = 1.0f;

    TileSet tileset(data.image, data.tileSize, data.xTiles, data.yTiles, scale);
    //TileMap2D tilemap(&tileset, (int)WIDTH/(data.tileSize.x*scale), (int)HEIGHT/(data.tileSize.y*scale));
    TileMap2D tilemap(&tileset, 30, 30);

    WFC wfc(&tilemap, parser.possibilities, parser.rules);

    int isometric = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(BLACK);

        wfc.update();
        //camera.offset = GetMousePosition();

        if (IsKeyDown(KEY_W)) {
            camera.target.y -= cameraSpeed;
        }
        if (IsKeyDown(KEY_S)) {
            camera.target.y += cameraSpeed;
        }
        if (IsKeyDown(KEY_A)) {
            camera.target.x -= cameraSpeed;
        }
        if (IsKeyDown(KEY_D)) {
            camera.target.x += cameraSpeed;
        }
        
        // Camera Zoom

        if (IsKeyDown(KEY_UP)) {
            camera.zoom -= 0.01;
        }
        if (IsKeyDown(KEY_DOWN)) {
            camera.zoom += 0.01;
        }


        if (IsKeyPressed(KEY_C))
            isometric = isometric == false ? true : false;

        if (isometric == false) 
            wfc.display();
        else if (isometric == true)
            tilemap.display(true);
        
        DrawFPS(0, 0);
        EndMode2D();
        EndDrawing();
    }

    //system("pause");
    Image finalImage = GenImageTilemap(&tilemap, true);
    ExportImage(finalImage, "result.png");

    CloseWindow();
    return 0;
}