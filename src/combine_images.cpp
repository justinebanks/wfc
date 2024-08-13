#include <iostream>
#include <vector>
#include <cmath>

#include <raylib/raylib.h>

#include "tileutils.hpp"

struct InputData {
    std::string inputDirectory;
    std::string outputDirectory;
    Vector2 tileSize;
    std::vector<std::string> images;
    std::vector<int> rotateSettings; // 0=None, 1=Rotate, 2=Flip
};

InputData pipeData = {
    "tilemaps/pipes/source_images/",
    "tilemaps/pipes/",
    {10, 10},
    {"corner.png", "cross.png", "empty.png", "line.png", "t.png"},
    {1, 1, 0, 1, 1}
};

InputData circleData = {
    "tilemaps/circles/source_images/",
    "tilemaps/circles/",
    {32, 32},
    {"b.png", "b_half.png", "b_i.png", "b_quarter.png", "w.png", "w_half.png", "w_i.png", "w_quarter.png"},
    {0, 1, 1, 1, 0, 1, 1, 1}
};

InputData roomData = {
    "tilemaps/rooms/source_images/",
    "tilemaps/rooms/",
    {3, 3},
    {"door.png", "empty.png", "side.png", "t.png", "turn.png", "wall.png", "bend.png", "corner.png", "corridor.png"},
    {1, 0, 1, 1, 1, 0, 1, 1, 1}
};


InputData townData = {
    "tilemaps/sketch-town/tiles/",
    "tilemaps/sketch-town/",
    {256, 352},
    {"grass_center_N.png", "grass_path_N.png", "grass_pathBend_N.png", "grass_pathCorner_N.png", "grass_pathCrossing_N.png", "grass_pathEnd_N.png", "grass_pathEndSquare_N.png", "grass_pathSplit_N.png"},
    {0, 2, 0, 0, 0, 2, 2, 2}
};

InputData cityData = {
    "tilemaps/city/source_images/",
    "tilemaps/city/",
    {133, 133},
    {"cityTiles_125.png", "cityTiles_126.png", "cityTiles_127.png", "cityTiles_000.png", "cityTiles_001.png", "cityTiles_002.png", "cityTiles_003.png", "cityTiles_004.png", "cityTiles_005.png", "cityTiles_006.png", "cityTiles_007.png", "cityTiles_008.png", "cityTiles_009.png", "cityTiles_010.png", "cityTiles_011.png", "cityTiles_012.png", "cityTiles_013.png", "cityTiles_014.png", "cityTiles_015.png", "cityTiles_016.png", "cityTiles_017.png", "cityTiles_018.png", "cityTiles_019.png", "cityTiles_020.png", "cityTiles_021.png", "cityTiles_022.png", "cityTiles_023.png", "cityTiles_024.png", "cityTiles_025.png", "cityTiles_026.png", "cityTiles_027.png", "cityTiles_028.png", "cityTiles_029.png", "cityTiles_030.png", "cityTiles_031.png", "cityTiles_032.png", "cityTiles_033.png", "cityTiles_034.png", "cityTiles_035.png", "cityTiles_036.png", "cityTiles_037.png", "cityTiles_038.png", "cityTiles_039.png", "cityTiles_040.png", "cityTiles_041.png", "cityTiles_042.png", "cityTiles_043.png", "cityTiles_044.png", "cityTiles_045.png", "cityTiles_046.png", "cityTiles_047.png", "cityTiles_048.png", "cityTiles_049.png", "cityTiles_050.png", "cityTiles_051.png", "cityTiles_052.png", "cityTiles_053.png", "cityTiles_054.png", "cityTiles_055.png", "cityTiles_056.png", "cityTiles_057.png", "cityTiles_058.png", "cityTiles_059.png", "cityTiles_060.png", "cityTiles_061.png", "cityTiles_062.png", "cityTiles_063.png", "cityTiles_064.png", "cityTiles_065.png", "cityTiles_066.png", "cityTiles_067.png", "cityTiles_068.png", "cityTiles_069.png", "cityTiles_070.png", "cityTiles_071.png", "cityTiles_072.png", "cityTiles_073.png", "cityTiles_074.png", "cityTiles_075.png", "cityTiles_076.png", "cityTiles_077.png", "cityTiles_078.png", "cityTiles_079.png", "cityTiles_080.png", "cityTiles_081.png", "cityTiles_082.png", "cityTiles_083.png", "cityTiles_084.png", "cityTiles_085.png", "cityTiles_086.png", "cityTiles_087.png", "cityTiles_088.png", "cityTiles_089.png", "cityTiles_090.png", "cityTiles_091.png", "cityTiles_092.png", "cityTiles_093.png", "cityTiles_094.png", "cityTiles_095.png", "cityTiles_096.png", "cityTiles_097.png", "cityTiles_098.png", "cityTiles_099.png", "cityTiles_100.png", "cityTiles_101.png", "cityTiles_102.png", "cityTiles_103.png", "cityTiles_104.png", "cityTiles_105.png", "cityTiles_106.png", "cityTiles_107.png", "cityTiles_108.png", "cityTiles_109.png", "cityTiles_110.png", "cityTiles_111.png", "cityTiles_112.png", "cityTiles_113.png", "cityTiles_114.png", "cityTiles_115.png", "cityTiles_116.png", "cityTiles_117.png", "cityTiles_118.png", "cityTiles_119.png", "cityTiles_120.png", "cityTiles_121.png", "cityTiles_122.png", "cityTiles_123.png", "cityTiles_124.png"},
    {}
};


int main() {
    InputData data = cityData;
    int rows = 2;
    int fold = 5;
    Color bgColor = Color{0,0,0,0};

    Image img;

    if (fold == 0)
        img = GenImageColor(data.tileSize.x*data.images.size(), data.tileSize.y*rows, bgColor);
    else
        img = GenImageColor(data.tileSize.x*fold, data.tileSize.y * floor(data.images.size()/fold) + 1, bgColor);

    for (int i = 0; i < data.images.size(); i++) {
        Image currentImg = LoadImage((data.inputDirectory + data.images[i]).c_str());
        
        if (fold == 0)
            ImageDrawImage(&img, { (float)data.tileSize.x*i, 133.0f - currentImg.height }, currentImg);
        else {
            float r = (float) floor(i / fold);
            ImageDrawImage(&img, { (float)(data.tileSize.x*(i % fold)), data.tileSize.y*r + 133.0f - currentImg.height }, currentImg);
        }

        if (data.rotateSettings.size() > 0) {
            if (data.rotateSettings[i] == 1) {
                ImageRotateCW(&currentImg);
                ImageDrawImage(&img, { (float)data.tileSize.x*i, (float)data.tileSize.y*1 }, currentImg);

                ImageRotateCW(&currentImg);
                ImageDrawImage(&img, { (float)data.tileSize.x*i, (float)data.tileSize.y*2 }, currentImg);

                ImageRotateCW(&currentImg);
                ImageDrawImage(&img, { (float)data.tileSize.x*i, (float)data.tileSize.y*3 }, currentImg);
            }

            if (data.rotateSettings[i] == 2) {
                ImageFlipHorizontal(&currentImg);
                ImageDrawImage(&img, { (float)data.tileSize.x*i, data.tileSize.y }, currentImg);
            }
        }


        UnloadImage(currentImg);
    }

    ExportImage(img, (data.outputDirectory + "tilemap.png").c_str());

    return 0;
}