#pragma once

#include <stack>
#include <string>
#include "lexer.h"
#include "symbole.h"

using namespace std;

class Etat;

class Automate {
public:
    Automate(const string& input);
    ~Automate();

    void lecture();

    void decalage(Symbole* s, Etat* e);
    void transitionsimple(Symbole* s, Etat* e);
    void reduction(int n, Symbole* s);

    Symbole* popSymbole();

private:
    Lexer lexer;
    stack<Etat*>    pileEtats;
    stack<Symbole*> pileSymboles;
};
