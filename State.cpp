//
// Created by Jonat on 30/10/2023.
//

#include "State.h"

State::State(const std::string &name) : name(name) {}

const std::string &State::getName() const {
    return name;
}

void State::setName(const std::string &name) {
    State::name = name;
}
