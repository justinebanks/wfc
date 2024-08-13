#pragma once

#include <raylib/raylib.h>
#include "tileset.hpp"
#include "tilemap.hpp"

// Converts From World Position To Tilemap Position
Vector2 worldToTile(TileMap2D *tilemap, Vector2 offset = {0,0});

// Converts From Tilemap Position to World Position
Vector2 tileToWorld(TileMap2D *tilemap, Vector2 tilePos, Vector2 offset = {0,0});

// Draws An Image Onto A Certain Position Within Another Image
void ImageDrawImage(Image *dst, Vector2 pos, Image image);

// Generates An Image From A TileMap
Image GenImageTilemap(TileMap2D *tilemap, bool isometric = false);

void saveTilemap(const char *filename, TileMap2D &tilemap);

TileMap2D loadTilemap(const char *filename, TileSet *tileset);