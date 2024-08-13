#include <iostream>
#include <fstream>
#include <unordered_map>
#include <stdexcept>

#include <raylib/raylib.h>
#include "json/json.h"

#include "rule_parser.hpp"


RuleParser::RuleParser(std::string filename) {
    std::ifstream file(filename);
    Json::Reader reader;

    reader.parse(file, data);

    std::unordered_map<std::string, std::vector<int>> aliasMap = parseAliases();
    parseRuleList(aliasMap);
}


std::unordered_map<std::string, std::vector<int>> RuleParser::parseAliases() {
    Json::Value aliases = data["aliases"];
    std::unordered_map<std::string, std::vector<int>> aliasMap;

    for (int i = 0; i < aliases.size(); i++) {
        Json::Value alias = aliases[i];
        std::string name = alias["name"].asString();


        std::vector<int> value;

        for (auto val : alias["value"]) {
            value.push_back(val.asInt());
        }

        aliasMap[name] = value;
    }
    this->aliasMap = aliasMap;
    return aliasMap;
}

std::vector<RuleSet> RuleParser::parseRuleList(std::unordered_map<std::string, std::vector<int>> aliasMap) {
    Json::Value rules = data["rules"];
    std::vector<RuleSet> allRules;

    for (int i = 0; i < rules.size(); i++) {
        Json::Value rule = rules[i];

        std::string name = rule["name"].asString();
        Vector2 tile = { rule["value"][0].asInt(), rule["value"][1].asInt() };

        for (int i = 0; i < rule["weight"].asInt(); i++) {
            this->possibilities.push_back(tile);
        }

        std::vector<std::vector<int>> types;

        for (auto type : rule["type"]) {
            types.push_back(aliasMap[type.asString()]);
        }

        if (types.size() != 4) {
            throw std::runtime_error("Type Must Have Size 4");
        }

        RuleSet newRule = { tile, types[0], types[1], types[2], types[3] };
        allRules.push_back(newRule);
    }

    this->rules = allRules;
    return allRules;
}

