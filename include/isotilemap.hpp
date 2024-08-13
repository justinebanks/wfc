#pragma once

#include <vector>

#include "tileset.hpp"
#include "raylib/raylib.h"
#include "tilemap.hpp"

class IsometricTilemap : public TileMap2D {
private:
    Vector2 isometricTransform(int x, int y, int z = 0);
public:
    TileSet *tileset;
    Vector2 cellCount;
    Vector2 totalSize;

    std::vector<std::vector<Vector2>> cells;

    IsometricTilemap(TileSet *tileset, int xCells, int yCells);
    void display(int xOffset = 0, int yOffset = 0);

    Vector2 getCell(int x, int y);
    void setCell(int x, int y, Vector2 value);

    bool isEmpty(int x, int y);
};