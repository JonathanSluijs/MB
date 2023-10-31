//
// Created by Jonat on 17/10/2023.
//


#include "ReadJson.h"

ReadJson::ReadJson(const std::string &filepath) : filepath(filepath) {
    std::ifstream input(filepath);
    input >> j;


}

std::vector<std::string> ReadJson::readTerminals() {
    std::vector<std::string> result;
    for(auto i : j["Terminals"]){
        result.push_back(i);
    }
    return result;
}

std::vector<std::string> ReadJson::readStates() {
    std::vector<std::string> result;
    for(auto i : j["States"]){
        result.push_back(i);
    }
    return result;
}

std::vector<std::string> ReadJson::readAlphabet() {
    std::vector<std::string> result;
    for(auto i : j["Alphabet"]){
        result.push_back(i);
    }
    return result;
}

std::vector<std::string> ReadJson::readStackAlphabet() {
    std::vector<std::string> result;
    for(auto i : j["StackAlphabet"]){
        result.push_back(i);
    }
    return result;
}

std::vector<std::string> ReadJson::readVariables() {
    std::vector<std::string> result;
    for(auto i : j["Variables"]){
        result.push_back(i);
    }
    return result;
}

std::vector<std::pair<std::string, std::vector<std::string>>> ReadJson::readProductions() {
    std::vector<std::pair<std::string, std::vector<std::string>>> result;
    for (const auto &production: j["Productions"]) {
        std::string head = production["head"];
        std::vector<std::string> body = production["body"];
        result.push_back(std::make_pair(head, body));
    }
    return result;
}


std::vector<Transition> ReadJson::readTransitions() {
    std::vector<Transition> result;
    for (const auto &production: j["Transitions"]) {
        result.push_back({production["from"],production["input"],production["stacktop"],production["to"],production["replacement"]});
    }
    return result;
}

std::string ReadJson::readStartSymbol() {
    return j["Start"];
}

std::string ReadJson::readStartState() {
    return j["StartState"];
}

std::string ReadJson::readStartStack() {
    return j["StartStack"];
}

