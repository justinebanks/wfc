#include <iostream>
#include <fstream>
#include <cmath>
#include <type_traits>

#include <raylib/raylib.h>
#include "json/json.h"
#include "tileset.hpp"
#include "tilemap.hpp"

#include "tileutils.hpp"

// Converts From World Position To Tilemap Position
Vector2 worldToTile(TileMap2D *tilemap, Vector2 offset) {
    Vector2 mouse = GetMousePosition();
    mouse.x -= offset.x;
    mouse.y -= offset.y;

    float mapCoordX = floor(mouse.x / tilemap->tileset->tileSize.x / tilemap->tileset->scale);
    float mapCoordY = floor(mouse.y / tilemap->tileset->tileSize.y / tilemap->tileset->scale);

    if (mapCoordX >= tilemap->cellCount.x || mapCoordY >= tilemap->cellCount.y || mapCoordX < 0 || mapCoordY < 0) 
        return Vector2{-1,-1};
    else
        return Vector2{mapCoordX, mapCoordY};
}


// Converts From Tilemap Position to World Position
Vector2 tileToWorld(TileMap2D *tilemap, Vector2 tilePos, Vector2 offset) {
    float worldCoordX = tilePos.x * tilemap->tileset->tileSize.x * tilemap->tileset->scale;
    float worldCoordY = tilePos.y * tilemap->tileset->tileSize.y * tilemap->tileset->scale;

    return Vector2{worldCoordX + offset.x, worldCoordY + offset.y};
}


// Draws An Image Onto A Certain Position Within Another Image
void ImageDrawImage(Image *dst, Vector2 pos, Image image) {
    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            Color color = GetImageColor(image, x, y);
            if (color.a > 0) ImageDrawPixel(dst, pos.x+x, pos.y+y, color);
        }
    }
}


// Generates An Image From A TileMap
Image GenImageTilemap(TileMap2D *tilemap, bool isometric) {
    Image image = GenImageColor(tilemap->totalSize.x, tilemap->totalSize.y, BLACK);

    for (int y = 0; y < tilemap->cellCount.y; y++) {
        for (int x = 0; x < tilemap->cellCount.x; x++) {
            Vector2 texPos = tilemap->getCell(x, y);
            Image inputImage = tilemap->tileset->getTileImage({texPos.x, texPos.y});
            Vector2 imgPos;

            if (isometric == false)
                imgPos = {
                    (float) x * tilemap->tileset->tileSize.x * tilemap->tileset->scale,
                    (float) y * tilemap->tileset->tileSize.y * tilemap->tileset->scale
                };
            else {
                Vector2 isoPos = tilemap->isometricTransform(x, y);
                imgPos = { isoPos.x + tilemap->totalSize.x/2, isoPos.y + tilemap->totalSize.y/4 };
            }

            ImageDrawImage(&image, imgPos, inputImage);
            UnloadImage(inputImage);
        }
    }

    return image;
}

void saveTilemap(const char *filename, TileMap2D &tilemap) {
    Json::Value data;
    std::ofstream file(filename);

    data["xCells"] = tilemap.cellCount.x;
    data["yCells"] = tilemap.cellCount.y;

    Json::Value cells = Json::Value(Json::arrayValue);

    for (int y = 0; y < tilemap.cellCount.y; y++) {
        Json::Value col = Json::Value(Json::arrayValue);

        for (int x = 0; x < tilemap.cellCount.x; x++) {
            Vector2 cell = tilemap.getCell(x, y);
            Json::Value row = Json::Value(Json::arrayValue);

            row.append(cell.x);
            row.append(cell.y);
            col.append(row);
        }

        cells.append(col);
    }

    data["cells"] = cells;

    file << data;
    //std::cout << data << std::endl;
}


TileMap2D loadTilemap(const char *filename, TileSet *tileset) {
    //static_assert(std::is_base_of<TileMap, T>::value, "T must inherit from TileMap");

    Json::Value data;
    Json::Reader reader;
    std::ifstream file(filename);

    reader.parse(file, data);

    int xCells = data["xCells"].asInt();
    int yCells = data["yCells"].asInt();

    TileMap2D newTilemap(tileset, xCells, yCells);
    Json::Value cells = data["cells"];

    for (int y = 0; y < yCells; y++) {
        for (int x = 0; x < xCells; x++) {
            Json::Value cell = cells[y][x];
            newTilemap.setCell(x, y, Vector2{cell[0].asFloat(), cell[1].asFloat()});
        }
    }

    return newTilemap;
}