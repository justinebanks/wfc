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











