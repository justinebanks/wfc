#include "isotilemap.hpp"
#include "tilemap.hpp"


Vector2 IsometricTilemap::isometricTransform(int x, int y, int z) {
    int width = 256;
    int height = 352;

    int xSpacing = 20;

    int yTransform = (height - width);

    return { x*(width/2 - xSpacing) - y*(width/2 - xSpacing), x*yTransform/2 + y*yTransform/2 - z*yTransform };
}


IsometricTilemap::IsometricTilemap(TileSet *tileset, int xCells, int yCells) {
    this->tileset = tileset;
    this->cellCount = { (float)xCells, (float)yCells };

    this->totalSize = Vector2{
        (float) tileset->tileSize.x * tileset->scale * xCells,
        (float) tileset->tileSize.y * tileset->scale * yCells
    };

    cells.resize(yCells, std::vector<Vector2>(xCells));

    for (int y = 0; y < yCells; y++) {
        for (int x = 0; x < xCells; x++) {
            setCell(x, y, {-1,-1});
        }
    }
}

void IsometricTilemap::display(int xOffset, int yOffset) {
    for (int y = 0; y < cellCount.y; y++) {
        for (int x = 0; x < cellCount.x; x++) {
            Vector2 position = isometricTransform(x, y);

            if (getCell(x, y).x != -1)
                tileset->drawTile(cells.at(y).at(x), {position.x + xOffset, position.y + yOffset});
        }
    }
}

Vector2 IsometricTilemap::getCell(int x, int y) {
    try {
        return cells.at(y).at(x);
    }
    catch (std::exception &e) {
        return Vector2{-1,-1}; // ERROR_TILE
    }
}


void IsometricTilemap::setCell(int x, int y, Vector2 value) {
    cells.at(y).at(x) = value;
}

bool IsometricTilemap::isEmpty(int x, int y) {
    Vector2 current = getCell(x, y);
    return current.x == -1 && current.y == -1;
}


