#pragma once

#include <vector>
#include <utility>
#include "tilemap.hpp"

struct RuleSet; // From rules.h OR rule_parser.hpp

// Wave Function Collapse Algorithm Implementation
class WFC 
{

private:
    // Utiliy Functions
    bool vectorEquals(std::vector<int> one, std::vector<int> two);
    RuleSet getRuleFromTex(Vector2 tex); // Gets the RuleSet associated with the specified tile coordinate

public:
    std::vector<std::vector<std::vector<Vector2>>> possibilities; // The grid of all possibilities corresponding to the same position in the tilemap's grid
    TileMap2D *tilemap; // TileMap used

    std::vector<Vector2> allPossibilities;
    std::vector<RuleSet> allRules;

    WFC(TileMap2D *tilemap, std::vector<Vector2> allPossibilities, std::vector<RuleSet> allRules);
    void display(); // Displays a grid of all the entropies for each tile

    int getCellEntropy(int x, int y); // Gets the entropy of a cell based on its current value in the 'possibilities' vector
    std::vector<Vector2> getCellPossibilities(int x, int y); // Returns all of the possibilities at a cell (just indexes the 'possibilities' vector)
    std::vector<Vector2> calculatePossibilities(int x, int y); // Re-calculates the possibilities at a given cell based on its neighbors and updates 'possibilities' vector accordingly

    void setCellPossibilities(int x, int y, std::vector<Vector2> p); // Sets the list of possibilities at a given cell

    int getLowestEntropy(); // Returns the lowest entropy in the grid
    std::vector<Vector2> getLeastCells(); // Returns all the cells whose entropies are equal to the lowest entropy

    void updateNeighbors(Vector2 pos, Vector2 tileType); // Re-Calculates the possibilities for all neighbors of the specified cell
    int update(); // Runs the next iteration of the Wave Function Collapse Algorithm
};