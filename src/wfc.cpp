#include <iostream>
#include <vector>
#include <string>

#include <ctime>
#include <cstdlib>
#include <cmath>

#include "tilemap.hpp"
#include "wfc.hpp"
#include "rule_parser.hpp"


bool WFC::vectorEquals(std::vector<int> one, std::vector<int> two) {
    //std::cout << "Sizes: " << one.size() << " " << two.size() << std::endl; 

    for (int i = 0; i < one.size(); i++) {
        if (one[i] != two[i]) 
            return false;
    }

    return true;
}


RuleSet WFC::getRuleFromTex(Vector2 tex) {
    for (int i = 0; i < allRules.size(); i++) {
        RuleSet rule = allRules.at(i);

        if (rule.tile.x == tex.x && rule.tile.y == tex.y) {
            return rule;
        }
    }

    return RuleSet{Vector2{-1,-1}, {}, {}, {}, {}}; // ERROR_TILE
}


WFC::WFC(TileMap2D *tilemap, std::vector<Vector2> allPossibilities, std::vector<RuleSet> allRules) {
    this->tilemap = tilemap;
    this->allPossibilities = allPossibilities;
    this->allRules = allRules;

    std::srand(std::time(nullptr));
    possibilities.resize(tilemap->cellCount.y, std::vector<std::vector<Vector2>>(tilemap->cellCount.x, std::vector<Vector2>(allPossibilities.size())));

    for (int y = 0; y < tilemap->cellCount.y; y++) {
        for (int x = 0; x < tilemap->cellCount.x; x++) {
            possibilities.at(y).at(x) = allPossibilities;
        }
    }
}


void WFC::display() {
    //std::cout << "Size: " << cells.size()

    for (int y = 0; y < tilemap->cellCount.y; y++) {
        for (int x = 0; x < tilemap->cellCount.x; x++) {
            Vector2 position = {
                (float)x*tilemap->tileset->tileSize.x*tilemap->tileset->scale, 
                (float)y*tilemap->tileset->tileSize.y*tilemap->tileset->scale
            };

            int entropy = getCellEntropy(x, y);
            std::string entropyString = std::to_string(entropy);
            Color color = entropy == 100 ? RED : entropy < 10 ? GREEN : WHITE;

            if (entropy == 0) {
                tilemap->tileset->drawTile(tilemap->cells.at(y).at(x), position);
            }
            else {
                DrawText(entropyString.c_str(), position.x, position.y, 30, color);
            }
        }
    }
}


int WFC::getCellEntropy(int x, int y) {
    int entropy = getCellPossibilities(x, y).size();
    if (tilemap->isEmpty(x, y))
        return entropy;
    else 
        return 0;
}


std::vector<Vector2> WFC::getCellPossibilities(int x, int y) {
    return possibilities.at(y).at(x);
}


std::vector<Vector2> WFC::calculatePossibilities(int x, int y) {
    if (x == -1 && y == -1) {
        return allPossibilities;
    }

    std::vector<int> n = getRuleFromTex(tilemap->getCell(x, y-1)).bottom;
    std::vector<int> e = getRuleFromTex(tilemap->getCell(x+1, y)).left;
    std::vector<int> s = getRuleFromTex(tilemap->getCell(x, y+1)).top;
    std::vector<int> w = getRuleFromTex(tilemap->getCell(x-1, y)).right;

    RuleSet rule = getRuleFromTex(tilemap->getCell(x, y));
    std::vector<Vector2> opts;


    for (auto r : allRules) {
        bool topEquals = true, bottomEquals = true, leftEquals = true, rightEquals = true;

        if (n.size() > 0 && !vectorEquals(r.top, n))
            topEquals = false;
        if (s.size() > 0 && !vectorEquals(r.bottom, s))
            bottomEquals = false;
        if (w.size() > 0 && !vectorEquals(r.left, w))
            leftEquals = false;
        if (e.size() > 0 && !vectorEquals(r.right, e))
            rightEquals = false;
        
        if (topEquals && bottomEquals && leftEquals && rightEquals)
            opts.push_back(r.tile);
    }

    if (opts.size() > 0)  {
        setCellPossibilities(x, y, opts);
        return opts;
    }
    else {
        //std::cout << "NO COMMON VALUES" << std::endl;
        //return allPossibilities
        return {{-1, -1}};
    }
}



void WFC::setCellPossibilities(int x, int y, std::vector<Vector2> p) {
    try {
        if (tilemap->isEmpty(x, y)) {
            possibilities.at(y).at(x) = p;
        }
    }
    catch (std::exception &e) {}
    
}


int WFC::getLowestEntropy() {
    int lowest = 255;

    for (int y = 0; y < tilemap->cellCount.y; y++) {
        for (int x = 0; x < tilemap->cellCount.x; x++) {
            int current = getCellEntropy(x, y);

            if (current < lowest && current > 0) // && tilemap->isEmpty(x, y)
                lowest = current;
        }
    }

    return lowest;
}


std::vector<Vector2> WFC::getLeastCells() {
    std::vector<Vector2> leasts;
    int lowest = getLowestEntropy();

    for (int y = 0; y < tilemap->cellCount.y; y++) {
        for (int x = 0; x < tilemap->cellCount.x; x++) {
            int current = getCellEntropy(x, y);

            if (current == lowest)
                leasts.push_back(Vector2{(float)x, (float)y});
        }
    }

    return leasts;
}


void WFC::updateNeighbors(Vector2 pos, Vector2 tileType) {
    //Vector2 tileType = tilemap->getCell(pos.x, pos.y);

    calculatePossibilities(pos.x-1, pos.y);
    calculatePossibilities(pos.x+1, pos.y);
    calculatePossibilities(pos.x, pos.y+1);
    calculatePossibilities(pos.x, pos.y-1);
}


int WFC::update() {
    std::vector<Vector2> leasts = getLeastCells();

    if (leasts.size() == 0) {
        //std::cout << "ARITHMETIC EXCEPTION: PROGRAM COMPLETED" << std::endl;
        return 0;
    }

    int randIndex = std::rand() % leasts.size();

    Vector2 selectedCoords = leasts[randIndex];
    std::vector<Vector2> tilePossibilities = calculatePossibilities(selectedCoords.x, selectedCoords.y);
    int tileEntropy = getCellEntropy(selectedCoords.x, selectedCoords.y);

    
    Vector2 randTex = tilePossibilities.at(std::rand() % tilePossibilities.size());
    tilemap->setCell(selectedCoords.x, selectedCoords.y, randTex);
    setCellPossibilities(selectedCoords.x, selectedCoords.y, {});

    updateNeighbors(selectedCoords, randTex);

    return 1;
}
