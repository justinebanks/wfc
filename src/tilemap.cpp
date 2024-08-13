#include <vector>
#include <raylib/raylib.h>

#include "tileset.hpp"
#include "tilemap.hpp"


TileMap2D::TileMap2D(TileSet *tileset, int xCells, int yCells) {
    this->tileset = tileset;
    this->cellCount = Vector2{ (float)xCells, (float)yCells };

    this->totalSize = Vector2{
        (float) tileset->tileSize.x * tileset->scale * xCells,
        (float) tileset->tileSize.y * tileset->scale * yCells
    };
    
    cells.resize(yCells, std::vector<Vector2>(xCells));

    // Initializes all cells to the designated default tile
    for (int y = 0; y < yCells; y++) {
        for (int x = 0; x < xCells; x++) {
            setCell(x, y, {-1, -1});
        }
    }
}


Vector2 TileMap2D::isometricTransform(int x, int y, int z) {
    int width = tileset->tileSize.x * tileset->scale;
    int height = tileset->tileSize.y * tileset->scale;

    int xSpacing = 0; //20;

    int yTransform = height/2; //(height - width);

    return { x*(width/2 - xSpacing) - y*(width/2 - xSpacing), x*yTransform/2 + y*yTransform/2 - z*yTransform };
}


void TileMap2D::display(bool isometric, int xOffset, int yOffset) {
    if (isometric) {
        for (int y = 0; y < cellCount.y; y++) {
            for (int x = 0; x < cellCount.x; x++) {
                Vector2 position = isometricTransform(x, y);

                if (getCell(x, y).x != -1)
                    tileset->drawTile(cells.at(y).at(x), {position.x + xOffset, position.y + yOffset});
            }
        }
    }
    else {
        for (int y = 0; y < cellCount.y; y++) {
            for (int x = 0; x < cellCount.x; x++) {
                Vector2 position = {
                    (float)x * tileset->tileSize.x*tileset->scale + xOffset, 
                    (float)y * tileset->tileSize.y*tileset->scale + yOffset
                };

                tileset->drawTile(cells.at(y).at(x), position);
            }
        }
    }
}


Vector2 TileMap2D::getCell(int x, int y) {
    try {
        return cells.at(y).at(x);
    }
    catch (std::exception &e) {
        return Vector2{-1,-1}; // ERROR_TILE
    }
}


void TileMap2D::setCell(int x, int y, Vector2 value) {
    cells.at(y).at(x) = value;
}


bool TileMap2D::isEmpty(int x, int y) {
    Vector2 current = getCell(x, y);
    return current.x == -1 && current.y == -1;
}

