//
// Created by Jonat on 30/10/2023.
//

#include "PDA.h"
PDA::PDA(const std::string &filepath) {
    // Initialize states, alphabet, stackAlphabet, transitions, startState, and startStack
    std::vector<std::string> stateStrings;
    std::vector<std::string> alphabetStrings;
    std::vector<std::string> stackAlphabetStrings;
    std::vector<Transition> transitionData;
    std::string startStateString;
    std::string startStackString;

    // Read JSON file and populate the above vectors and strings
    ReadJson r(filepath);
    stateStrings = r.readStates();
    alphabetStrings = r.readAlphabet();
    stackAlphabetStrings = r.readStackAlphabet();
    transitionData = r.readTransitions();
    startStateString = r.readStartState();
    startStackString = r.readStartStack();

    // Initialize states
    for (const auto& stateStr : stateStrings) {
        states.insert(new State(stateStr));
    }

    // Initialize alphabet and stackAlphabet
    alphabet.insert(alphabetStrings.begin(), alphabetStrings.end());
    stackAlphabet.insert(stackAlphabetStrings.begin(), stackAlphabetStrings.end());

    // Initialize transitions
    for (const auto& tdata : transitionData) {
        transitions.push_back(Transition(tdata));
    }

    // Initialize startState and startStack
    startState = findState(startStateString);
    startStack = startStackString;
}

State* PDA::findState(const std::string &stateName) const {
    // Loop through the states set
    for (const auto& state : states) {
        if (state->getName() == stateName) {
            return state;
        }
    }

    return nullptr;  // Return nullptr if no match is found
}

CFG PDA::toCFG() {
    CFG cfg;

    // add Non-terminals
    cfg.addToNonTerminals("S");
    for (State* state1 : states) {
        for (const std::string& stackSym : stackAlphabet) {
            for (State* state2 : states) {
                cfg.addToNonTerminals("[" +state1->getName() + "," + stackSym + "," + state2->getName()+ "]");
            }
        }
    }
    // add terminals
    for(auto t : alphabet){
        cfg.addToTerminals(t);
    }



// Add productions based on transitions
    for (const Transition& t : transitions) {
        std::string from = t.from;
        std::string to = t.to;
        std::string input = t.input;


        if (t.replacement.empty()) {
            std::vector<Symbol*> bodySymbols;
            if (!input.empty()) bodySymbols.push_back(new Terminal(input));
            cfg.addToProductions(new Production(cfg.findSymbol("[" + from + "," + t.stacktop + "," + to + "]"), bodySymbols));
        }
        else if (t.replacement.size() == 1){
            for (State* s : states){
                cfg.addToProductions(new Production(cfg.findSymbol("[" + from + "," + t.stacktop + "," + s->getName() + "]"),{cfg.findSymbol(input),cfg.findSymbol("[" + from + "," + t.replacement[0] + "," + s->getName() + "]")}));
            }
        }
        else if (t.replacement.size() == 2) {
            for (State* r : states) {
                for (State* s : states) {
                    std::vector<Symbol*> bodySymbols;
                    bodySymbols.push_back(new Terminal(input));
                    bodySymbols.push_back(cfg.findSymbol("[" + to + "," + t.replacement[0] + "," + r->getName() + "]"));
                    bodySymbols.push_back(cfg.findSymbol("[" + r->getName() + "," + t.replacement[1] + "," + s->getName() + "]"));
                    cfg.addToProductions(new Production(cfg.findSymbol("[" + from + "," + t.stacktop + "," + s->getName() + "]"), bodySymbols));
                }
            }
        }
    }

    //Setting the start symbol
    cfg.setStartSymbol(cfg.findSymbol("[" + startState->getName() + "," + startState->getName() + "]"));
    for (State* s : states) {
        cfg.addToProductions(new Production(cfg.findSymbol("S"), {cfg.findSymbol("[" + startState->getName() + "," + startStack + "," + s->getName() + "]")}));
    }
    cfg.setStartSymbol(new NonTerminal("S"));

    return cfg;




}

// Print function just for testing
void PDA::print() const {
    std::cout << "States: ";
    for (const auto &state : states) {
        std::cout << state << " ";
    }
    std::cout << "\n";

    std::cout << "Alphabet: ";
    for (const auto &symbol : alphabet) {
        std::cout << symbol << " ";
    }
    std::cout << "\n";

    std::cout << "Stack Alphabet: ";
    for (const auto &symbol : stackAlphabet) {
        std::cout << symbol << " ";
    }
    std::cout << "\n";

    std::cout << "Transitions:\n";
    for (const auto &transition : transitions) {
        std::cout << transition.from << " -> " << transition.input << " / " << transition.stacktop << " -> " << transition.to << " / ";
        for (const auto &replace : transition.replacement) {
            std::cout << replace << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Start State: " << startState->getName() << "\n";
    std::cout << "Start Stack: " << startStack << "\n";
}
