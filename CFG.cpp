//
// Created by Jonat on 16/10/2023.
//

#include "CFG.h"

CFG::CFG() {}

CFG::CFG(std::string filepath) {
    // Initialize non-terminals, terminals, productions, and startSymbol
    std::vector<std::string> nonTerminalStrings;
    std::vector<std::string> terminalStrings;
    std::vector<std::pair<std::string, std::vector<std::string>>> productionStrings;
    std::string startString;

    // Read JSON file and populate the above vectors and startString
    ReadJson r(filepath);
    nonTerminalStrings = r.readVariables();
    terminalStrings = r.readTerminals();
    productionStrings = r.readProductions();
    startString = r.readStartSymbol();

    // Initialize nonTerminals
    for (const auto& symbol : nonTerminalStrings) {
        nonTerminals.insert(new NonTerminal(symbol));
    }

    // Initialize terminals
    for (const auto& symbol : terminalStrings) {
        terminals.insert(new Terminal(symbol));
    }

    // Initialize productions
    for (const auto& production : productionStrings) {
        std::string head = production.first;
        std::vector<std::string> bodyStrings = production.second;
        std::vector<Symbol*> body;

        // Convert body strings to symbols
        for (const auto& symbol : bodyStrings) {
            // Determine whether the symbol is a terminal or non-terminal
            Symbol* symbolPtr = findSymbol(symbol);
            if (symbolPtr != nullptr) {
                body.push_back(symbolPtr);
            }
        }


        addToProductions(new Production(findSymbol(head, false), body));
    }

    // Initialize startSymbol
    startSymbol = findSymbol(startString, false);
}

void CFG::print() const {


    // Print non-terminals
    std::cout << "V = {";
    bool isFirst = true;
    for (const Symbol* symbol : nonTerminals) {
        if (!isFirst) {
            std::cout << ", ";
        }
        std::cout << symbol->getSymbol();
        isFirst = false;
    }
    std::cout << "}" << std::endl;

    // Print terminals
    std::cout << "T = {";
    isFirst = true;
    for (const Symbol* symbol : terminals) {
        if (!isFirst) {
            std::cout << ", ";
        }
        std::cout << symbol->getSymbol();  // Removed backticks for terminals
        isFirst = false;
    }
    std::cout << "}" << std::endl;




    // Print productions
    std::cout << "P = {" << std::endl;
    for (const Production* production : productions) {
        std::cout << "    " << production->getHead()->getSymbol() << " -> ";
        const std::vector<Symbol*>& body = production->getBody();
        if (body.empty()) {
            std::cout << "``"; // For epsilon productions
        } else {
            std::cout << "`";
            for (size_t i = 0; i < body.size(); i++) {
                if (i > 0) std::cout << " ";
                // Add backticks only for terminal symbols
                std::cout<< body[i]->getSymbol();
                if(i == body.size()-1){
                    std::cout << "`";
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "}" << std::endl;

    // Print start symbol
    std::cout << "S = " << startSymbol->getSymbol() << std::endl;
}



Symbol* CFG::findSymbol(const std::string& inputSymbol, bool isTerminal) const {
    if(isTerminal){
        for (const auto& symbol : terminals) {
            if (symbol->getSymbol() == inputSymbol) {
                return symbol;
            }
        }
    }else{
        for (const auto& symbol : nonTerminals) {
            if (symbol->getSymbol() == inputSymbol) {
                return symbol;
            }
        }
    }

    return nullptr; // Symbol not found
}

Symbol* CFG::findSymbol(const std::string& inputSymbol) const {
        for (const auto& symbol : terminals) {
            if (symbol->getSymbol() == inputSymbol) {
                return symbol;
            }
        }

        for (const auto& symbol : nonTerminals) {
            if (symbol->getSymbol() == inputSymbol) {
                return symbol;
            }
        }
    return nullptr; // Symbol not found
}

bool CFG::addToTerminals(const std::string& symbol){
    terminals.insert(new Terminal(symbol));
    return true;
}

bool CFG::addToProductions(Production* production){
    productions.insert(production);
    return true;
}

bool CFG::addToNonTerminals(const std::string& symbol){
    nonTerminals.insert(new NonTerminal(symbol));
    return true;
}

const std::set<Symbol *, decltype(&Symbol::compare)> &CFG::getNonTerminals() const {
    return nonTerminals;
}

void CFG::setNonTerminals(const std::set<Symbol *, decltype(&Symbol::compare)> &nonTerminals) {
    CFG::nonTerminals = nonTerminals;
}

const std::set<Symbol *, decltype(&Symbol::compare)> &CFG::getTerminals() const {
    return terminals;
}

void CFG::setTerminals(const std::set<Symbol *, decltype(&Symbol::compare)> &terminals) {
    CFG::terminals = terminals;
}

const std::set<Production*, decltype(&Production::compare)> &CFG::getProductions() const {
    return productions;
}

void CFG::setProductions(std::set<Production*, decltype(&Production::compare)> &productions) {
    CFG::productions = productions;
}

Symbol *CFG::getStartSymbol() const {
    return startSymbol;
}

void CFG::setStartSymbol(Symbol *startSymbol) {
    CFG::startSymbol = startSymbol;
}

