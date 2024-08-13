#pragma once

#include <vector>
#include <raylib/raylib.h>
#include "tileset.hpp"


class TileMap2D {
public:
    TileSet *tileset;
    Vector2 cellCount;
    Vector2 totalSize;

    std::vector<std::vector<Vector2>> cells;

    TileMap2D() {};
    TileMap2D(TileSet *tileset, int xCells, int yCells);

    Vector2 isometricTransform(int x, int y, int z = 0);
    void display(bool isometric = false, int xOffset = 0, int yOffset = 0) ;

    Vector2 getCell(int x, int y);
    void setCell(int x, int y, Vector2 value);
    bool isEmpty(int x, int y);
};

