//
// Created by Jonat on 16/10/2023.
//

#include "Production.h"


Production::Production(Symbol *head, const std::vector<Symbol *> &body) : head(head),
                                                                          body(body) {}

const Symbol *Production::getHead() const {
    return head;
}

void Production::setHead(Symbol *head) {
    Production::head = head;
}

const std::vector<Symbol *> &Production::getBody() const {
    return body;
}

void Production::setBody(const std::vector<Symbol *> &body) {
    Production::body = body;
}

bool Production::compare(const Production* a, const Production* b) {
    //  Compare the heads
    if (a->getHead() != b->getHead()) {
        return a->getHead()->getSymbol() < b->getHead()->getSymbol();
    }

    // Compare the bodies lexicographically
    return std::lexicographical_compare(
            a->getBody().begin(), a->getBody().end(),
            b->getBody().begin(), b->getBody().end(),
            [](const Symbol* s1, const Symbol* s2) {
                return s1->getSymbol() < s2->getSymbol();
            });
}