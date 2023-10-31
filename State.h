//
// Created by Jonat on 30/10/2023.
//

#ifndef INC_1_STATE_H
#define INC_1_STATE_H
#include "iostream"
#include "Symbol.h"

class State {
public:
    explicit State(const std::string &name);

    const std::string &getName() const;

    void setName(const std::string &name);

private:
    std::string name;
};


#endif //INC_1_STATE_H
