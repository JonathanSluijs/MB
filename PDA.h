//
// Created by Jonat on 30/10/2023.
//

#ifndef INC_1_PDA_H
#define INC_1_PDA_H
#include "ReadJson.h"
#include <vector>
#include "iostream"
#include "State.h"
#include "CFG.h"
#include <set>

class PDA {
public:
    PDA(const std::string &filepath);

    void print() const;

    CFG toCFG();

    State* findState(const std::string &stateName) const;
private:
    std::set<State*> states;
    std::set<std::string> alphabet;
    std::set<std::string> stackAlphabet;
    std::vector<Transition> transitions;
    State* startState;
    std::string startStack;
};


#endif //INC_1_PDA_H
