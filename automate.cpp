#include "automate.h"
#include "etat.h"
#include <iostream>

Automate::Automate(const string& input) : lexer(input) {}

Automate::~Automate() {
    while (!pileEtats.empty()) {
        delete pileEtats.top();
        pileEtats.pop();
    }
    while (!pileSymboles.empty()) {
        delete pileSymboles.top();
        pileSymboles.pop();
    }
}

void Automate::lecture() {
    pileEtats.push(new Etat0());

    bool continuer = true;
    while (continuer) {
        Symbole* s = lexer.Consulter();
        continuer = pileEtats.top()->transition(*this, s);
    }

    // Result is on top of the symbol stack
    Expr* result = dynamic_cast<Expr*>(pileSymboles.top());
    if (result) {
        map<string, double> vide;
        cout << result->eval(vide) << endl;
    } else {
        cerr << "Erreur de syntaxe" << endl;
    }
}

void Automate::decalage(Symbole* s, Etat* e) {
    pileSymboles.push(s);
    pileEtats.push(e);
    lexer.Avancer();
}

void Automate::transitionsimple(Symbole* s, Etat* e) {
    pileSymboles.push(s);
    pileEtats.push(e);
}

void Automate::reduction(int n, Symbole* s) {
    for (int i = 0; i < n; i++) {
        delete pileEtats.top();
        pileEtats.pop();
    }
    pileEtats.top()->transition(*this, s);
}

Symbole* Automate::popSymbole() {
    Symbole* s = pileSymboles.top();
    pileSymboles.pop();
    return s;
}
