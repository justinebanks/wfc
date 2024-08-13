#include <iostream>

#include <raylib/raylib.h>
#include "tileset.hpp"
#include "tilemap.hpp"
#include "tileutils.hpp"

#define WIDTH 1366
#define HEIGHT 768

#define TILE_SIZE {16, 16}
#define TILE_SCALE 4

Vector2 currentSelection = {-1, -1};

int main(int argc, char *argv[]) {
    const std::string inputImg = argv[1];
    const int inputX = atoi(argv[2]);
    const int inputY = atoi(argv[3]);

    const std::string outputImg = argv[4];
    const int outputX = atoi(argv[5]);
    const int outputY = atoi(argv[6]);

    const char *externalPreset = argv[7];

    InitWindow(WIDTH, HEIGHT, "TileMap Maker");
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    std::cout << "INFO: " << inputImg << " -> " << outputImg << std::endl;

    //TileSet tileset(INPUT_IMG, TILE_SIZE, INPUT_X_TILES, INPUT_Y_TILES, TILE_SCALE);
    TileSet tileset(inputImg.c_str(), TILE_SIZE, inputX, inputY, TILE_SCALE);


    TileMap2D selector(&tileset, tileset.xTiles, tileset.yTiles);
    TileMap2D tilemap(&tileset, outputX, outputY);   

    if (externalPreset)
        tilemap = loadTilemap(externalPreset, &tileset);

    // Initialize Selector Tilemap
    for (int y = 0; y < tileset.yTiles; y++) {
        for (int x = 0; x < tileset.xTiles; x++) {
            Vector2 tex = { (float)x, (float)y };
            selector.setCell(x, y, tex);
        }
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        Vector2 gridOffset = {GetScreenWidth()-tilemap.totalSize.x, 0};        

        if (IsMouseButtonPressed(0)) {
            // Handle Tile Texture Selection
            Vector2 selection = worldToTile(&selector);
            //std::cout << "Selection: " << selection.x << ", " << selection.y << std::endl;
            
            if (selection.x != -1) 
                currentSelection = selection;
            else {
                // Handle Grid Position Selection
                Vector2 position = worldToTile(&tilemap, gridOffset);
                //std::cout << "Position: " << position.x << ", " << position.y << std::endl;

                if (position.x != -1)
                    tilemap.setCell(position.x, position.y, currentSelection);
            }
        }

        // Display Tilemaps
        selector.display();
        tilemap.display(false, gridOffset.x, gridOffset.y);
    
        DrawRectangleLines(gridOffset.x, gridOffset.y, tilemap.totalSize.x, tilemap.totalSize.y, WHITE);
        DrawText("Press S To Save Tilemap", 10, GetScreenHeight()-100, 60, WHITE);

        // Save Image To File
        if (IsKeyPressed(KEY_S)) {
            std::cout << "Exporting Image ..." << std::endl;
            Image finalImage = GenImageTilemap(&tilemap);
            ExportImage(finalImage, outputImg.c_str());

            std::cout << "Writing JSON" << std::endl;
            saveTilemap((outputImg + ".json").c_str(), tilemap);

            std::cout << "Program Complete" << std::endl;
            CloseWindow();
            return 0;
        }

        // Draw Rectangle To Indicate Current Tile Selection
        if (currentSelection.x != -1) {
            Vector2 worldCoords = tileToWorld(&tilemap, currentSelection);
            Vector2 tileSize = {tileset.tileSize.x * tileset.scale, tileset.tileSize.y * tileset.scale};
            Rectangle rect = {worldCoords.x, worldCoords.y, (float)tileSize.x, (float)tileSize.y};
            DrawRectangleLinesEx(rect, 5, YELLOW);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

