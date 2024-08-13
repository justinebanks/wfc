#include <iostream>
#include <raylib/raylib.h>

#include "tileset.hpp"


TileSet::TileSet(const char *filename, Vector2 tileSize, int xTiles, int yTiles, int scale = 1) {

    // Creates an Image from the file and loads it to a Texture2D
    img = LoadImage(filename);
    ImageResize(&img, xTiles*tileSize.x*scale, yTiles*tileSize.y*scale);
    texture = LoadTextureFromImage(img);

    this->scale = scale;
    this->tileSize = tileSize;
    this->xTiles = xTiles;
    this->yTiles = yTiles;
}


TileSet::~TileSet() {
    UnloadImage(img);
    UnloadTexture(texture);
}


void TileSet::setScale(float value) {
    ImageResize(&img, xTiles*tileSize.x*value/scale, yTiles*tileSize.y*value/scale);
    UnloadTexture(texture);
    texture = LoadTextureFromImage(img);
    scale = value;
}


Rectangle TileSet::getTile(Vector2 pos) {
    if (pos.x == -1 || pos.y == -1) {
        //std::cout << "SILENT ERROR: TRIED TO ACCESS TILE AT POSITION (-1, -1)" << std::endl;
        pos = {0,0};
    }

    return Rectangle{pos.x*tileSize.x*scale, pos.y*tileSize.y*scale, (float)tileSize.x*scale, (float)tileSize.y*scale};
}


Image TileSet::getTileImage(Vector2 pos) {
    if (pos.x == -1 || pos.y == -1) {
        //std::cout << "SILENT ERROR: TRIED TO ACCESS TILE AT POSITION (-1, -1)" << std::endl;
        return GenImageColor(tileSize.x*scale, tileSize.y*scale, Color{0,0,0,1});
    }

    Rectangle rect = getTile(pos);
    return ImageFromImage(img, rect); // The user is responsible for freeing the memory :)
}


void TileSet::drawTile(Vector2 texCoord, Vector2 position) {
    if (texCoord.x == -1 || texCoord.y == -1) {
        DrawRectangleV(position, {(float)tileSize.x*scale, (float)tileSize.y*scale}, BLACK);
        return;
    }

    DrawTextureRec(texture, getTile(texCoord), position, WHITE);
}



