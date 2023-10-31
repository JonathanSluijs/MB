//
// Created by Jonat on 17/10/2023.
//
#include "iostream"
#include <fstream>
#include "json.hpp"
#ifndef INC_1_READJSON_H
#define INC_1_READJSON_H
using json = nlohmann::json;

struct Transition {
    std::string from;
    std::string input;
    std::string stacktop;
    std::string to;
    std::vector<std::string> replacement;
};

class ReadJson {
public:
    explicit ReadJson(const std::string &filepath);

    std::vector<std::string>readVariables();

    std::vector<std::string>readTerminals();

    std::vector<std::pair<std::string, std::vector<std::string>>> readProductions();

    std::string readStartSymbol();

    std::string readStartState();

    std::string readStartStack();

    std::vector<Transition> readTransitions();

    std::vector<std::string> readStackAlphabet();

    std::vector<std::string> readAlphabet();

    std::vector<std::string> readStates();
private:
std::string filepath;
json j;
};


#endif //INC_1_READJSON_H
