#pragma once

#include <raylib/raylib.h>

// Should Probably Add Support For Possible Spacing Between Tiles

class TileSet {
public:
    Image img;
    Texture2D texture;
    Vector2 tileSize; // Size of Each Tile In Pixels

    // Tileset Dimensions
    int xTiles;
    int yTiles;

    // How Much To Rescale The Tileset
    int scale;

    TileSet(const char *filename, Vector2 tileSize, int xTiles, int yTiles, int scale);
    ~TileSet();

    void setScale(float value);
    Rectangle getTile(Vector2 pos); // Gets the Rectangle representing a specific coordinate (Vector2) in the TileSet
    Image getTileImage(Vector2 pos); // Gets The Image Associated With the Specified Position in the Tileset
    void drawTile(Vector2 texCoord, Vector2 position); // Draws the specified 'texCoord' tile to the screen as the position 'position'
};


