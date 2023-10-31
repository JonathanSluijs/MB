//
// Created by Jonat on 16/10/2023.
//
#include <vector>
#include "iostream"
#include "Symbol.h"
#ifndef INC_1_PRODUCTION_H
#define INC_1_PRODUCTION_H


class Production {
public:
    Production(Symbol *head, const std::vector<Symbol *> &body);

    static bool compare(const Production* a, const Production* b);

    const Symbol *getHead() const;

    void setHead(Symbol *head);

    const std::vector<Symbol *> &getBody() const;

    void setBody(const std::vector<Symbol *> &body);

private:
    Symbol* head;
    std::vector<Symbol*> body;
};


#endif //INC_1_PRODUCTION_H
