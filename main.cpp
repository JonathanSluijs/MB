#include "PDA.h"

using namespace std;

int main() {
    PDA pda("../input.json");
    pda.toCFG().print();

    return 0;
}