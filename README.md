# Wave Function Collapse (Raylib)
This is my implementation of the Wave Function Collapse Algorithm, inspired by [this popular repository](https://github.com/mxgmn/WaveFunctionCollapse). This is a set of tools that can be used to for random tilemap generation in raylib.

It includes, a TileSet and TileMap class for taking in organized tileset image data and rendering it to the screen, and then a WFC class for performing the algorithm on the TileMap passed to it.

## Building the Project
I don't know CMake yet, so I made a simple Makefile that compiles tilemap.cpp, tileset.cpp, and tileutils.cpp into libtiles.a and then compiles wfc.cpp and rule_parser.cpp into libwfc.a. Then, I linked both static libraries to the main file. 

To build this project, you can just run make (or mingw32-make for windows MinGW) in the terminal.
```bash
make all
mingw32-make all
```

This project relies on the static library for jsoncpp and raylib, which are in the 'lib' folder with libtiles and libwfc. If it's inconvenient to use static libraries you can edit a few simple stuff in the Makefile to get DLLs or Shared Object Files.

## Executable Files (Bin Folder)
There are 3 main executable files: main.cpp, combine_images.cpp, and tilemap_maker.cpp. The main.cpp file is a simple example of how to use this project. Other than the normal raylib boilerplate code, it passes a tileset image and its dimensions to the TileSet class, passes its pointer to the TileMap2D class, and then passes that to the WFC class along with a standard vector of Vector2 structs representing all the the tileset position that you wish to be used in the algorithm and another vector of all the rules for each tile.

This an example of what I just explained:
```cpp
int main() {
    const char *img = "res/image"; // 20x30 tileset of 16px images
    
    TileSet tileset(img, 16, 20, 30, 1); // Last Parameter is the scale of the image
    TileMap tilemap(&tileset, 20, 20); // Instantiates a 30x30 tilemap;
    
    RuleParser parser("rule_file.json"); // All Rules Are Specified in a JSON File (explained later)
    
    WFC wfc(&tilemap, parser.possibilities, parser.rules);
    ...
}
```

After setting up all the initializations, getting the program to work is as simple as adding this code to the game loop:
```cpp
while (!WindowShouldClose()) {
    BeginDrawing();
    
    wfc.update();
    tilemap.display();
    
    EndDrawing();
}
```

All the example JSON rulesets are in tile 'tilemaps' folder. Given a set of images, I 'combine_images.cpp' as a utility script to combine all the indivisual source images into one big tileset that I can use in my program. To use it, just go to src/combine_images.cpp and create a new InputData variable to use in the main function
```cpp
InputData myData = {
    "tilemaps/pipes/source_images/", // Source Image Directory
    "tilemaps/pipes/",              // Output Directory
    {10, 10},                       // Image Size
    {"corner.png", "cross.png", "empty.png", "line.png", "t.png"}, // List of Images
    {1, 1, 0, 1, 1} // Rotation Settings for Each Image (Can be used to add flipped and roated versions to the tileset)
};

int main() {
    InputData data = myData;
    ...
}
```
If you already have a tileset to use, then you don't need to do this of course. Now, to define all the rules create a JSON file with a general structure like this:
```json
{
    "aliases": [
    {
        "name": "ALIAS1",
        "value": [1]
    },
    {
        "name": "ALIAS2",
        "value": [2]
    }
    }
    ],
    "rules": [
        {
            "name": "Tile 1",
            "value": [0, 0],
            "weight": 1,
            "type": ["ALIAS1", "ALIAS2", "ALIAS1", "ALIAS2"]
        },
    ]
}
```

There are 2 aliases in this example: ALIAS1 and ALIAS2. There is one rule. The "name" (Tile 1) is just for the user's convenience, the "value" is the tile's position in the tileset that will be used, the "weight" is not working yet and just needs to be there as 1 so that you don't get any errors, and finally "type" defines what can be present at the top, bottom, left, and right of the tile (in that order).

In this example, "Tile 1" can only have a tile who's "bottom" is set "ALIAS1" above it. and only a tile who's top is set to "ALIAS2" below it. So the "type" defines the "connectors" on the top, bottom, left, and right of the tile. Do this for all tiles that you want to use, and then import this rule set along with the image into the program as I showed above and the program should work perfectly












