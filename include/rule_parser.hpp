#pragma once

#include <unordered_map>

#include <raylib/raylib.h>
#include "json/json.h"


struct RuleSet {
    Vector2 tile;

    std::vector<int> top;
    std::vector<int> bottom;
    std::vector<int> left;
    std::vector<int> right;

};


class RuleParser {
public:
    Json::Value data;
    std::vector<RuleSet> rules;
    std::unordered_map<std::string, std::vector<int>> aliasMap;
    std::vector<Vector2> possibilities;

    RuleParser(std::string filename);

private:
    std::unordered_map<std::string, std::vector<int>> parseAliases();
    std::vector<RuleSet> parseRuleList(std::unordered_map<std::string, std::vector<int>> aliasMap);
};


