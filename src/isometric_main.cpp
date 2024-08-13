#include <iostream>
#include <cmath>

#include <raylib/raylib.h>
#include "tileset.hpp"
#include "tilemap.hpp"
#include "wfc.hpp"

int main() {
    InitWindow(1366, 768, "Isometric WFC");
    SetTargetFPS(60);

    TileSet tileset("tilemaps/city/tilemap.png", {133, 133}, 5, 25, 1);
    TileMap2D tilemap(&tileset, 3, 2);

    tilemap.setCell(0, 0, {0,13});
    tilemap.setCell(1, 0, {1,13});
    tilemap.setCell(2, 0, {2,13});
    tilemap.setCell(2, 1, {3,13});

    while (!WindowShouldClose()) {
        BeginDrawing();

        tilemap.display(true);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}