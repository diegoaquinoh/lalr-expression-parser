#include "etat.h"
#include "automate.h"
#include <iostream>

void Etat::print() const {
    cout << name << endl;
}

// State 0: Initial state
// val->d3, (->d2, E->1
bool Etat0::transition(Automate& automate, Symbole* s) {
    switch (*s) {
        case INT:
            automate.decalage(s, new Etat3());
            return true;
        case OPENPAR:
            automate.decalage(s, new Etat2());
            return true;
        case EXPR:
            automate.transitionsimple(s, new Etat1());
            return true;
        default:
            cerr << "Erreur de syntaxe (E0)" << endl;
            return false;
    }
}

// State 1: E' -> E .  (accept on $, shift on + and *)
// +->d4, *->d5, $->accept
bool Etat1::transition(Automate& automate, Symbole* s) {
    switch (*s) {
        case PLUS:
            automate.decalage(s, new Etat4());
            return true;
        case MULT:
            automate.decalage(s, new Etat5());
            return true;
        case FIN:
            return false; // accept
        default:
            cerr << "Erreur de syntaxe (E1)" << endl;
            return false;
    }
}

// State 2: E -> ( . E )
// val->d3, (->d2, E->6
bool Etat2::transition(Automate& automate, Symbole* s) {
    switch (*s) {
        case INT:
            automate.decalage(s, new Etat3());
            return true;
        case OPENPAR:
            automate.decalage(s, new Etat2());
            return true;
        case EXPR:
            automate.transitionsimple(s, new Etat6());
            return true;
        default:
            cerr << "Erreur de syntaxe (E2)" << endl;
            return false;
    }
}

// State 3: E -> val .  (reduce rule 5 on all terminals)
// +->r5, *->r5, )->r5, $->r5
bool Etat3::transition(Automate& automate, Symbole* s) {
    switch (*s) {
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN: {
            // Reduce rule 5: E -> val
            Entier* entier = dynamic_cast<Entier*>(automate.popSymbole());
            Nombre* nombre = new Nombre(entier->getValeur());
            delete entier;
            automate.reduction(1, nombre);
            return true;
        }
        default:
            cerr << "Erreur de syntaxe (E3)" << endl;
            return false;
    }
}

// State 4: E -> E + . E
// val->d3, (->d2, E->7
bool Etat4::transition(Automate& automate, Symbole* s) {
    switch (*s) {
        case INT:
            automate.decalage(s, new Etat3());
            return true;
        case OPENPAR:
            automate.decalage(s, new Etat2());
            return true;
        case EXPR:
            automate.transitionsimple(s, new Etat7());
            return true;
        default:
            cerr << "Erreur de syntaxe (E4)" << endl;
            return false;
    }
}

// State 5: E -> E * . E
// val->d3, (->d2, E->8
bool Etat5::transition(Automate& automate, Symbole* s) {
    switch (*s) {
        case INT:
            automate.decalage(s, new Etat3());
            return true;
        case OPENPAR:
            automate.decalage(s, new Etat2());
            return true;
        case EXPR:
            automate.transitionsimple(s, new Etat8());
            return true;
        default:
            cerr << "Erreur de syntaxe (E5)" << endl;
            return false;
    }
}

// State 6: E -> ( E . )  inside parentheses
// +->d4, *->d5, )->d9
bool Etat6::transition(Automate& automate, Symbole* s) {
    switch (*s) {
        case PLUS:
            automate.decalage(s, new Etat4());
            return true;
        case MULT:
            automate.decalage(s, new Etat5());
            return true;
        case CLOSEPAR:
            automate.decalage(s, new Etat9());
            return true;
        default:
            cerr << "Erreur de syntaxe (E6)" << endl;
            return false;
    }
}

// State 7: E -> E + E .  (reduce rule 2, but shift on *)
// +->r2, *->d5, )->r2, $->r2
bool Etat7::transition(Automate& automate, Symbole* s) {
    switch (*s) {
        case MULT:
            // Precedence: * > +, shift
            automate.decalage(s, new Etat5());
            return true;
        case PLUS:
        case CLOSEPAR:
        case FIN: {
            // Reduce rule 2: E -> E + E
            Expr* droite = dynamic_cast<Expr*>(automate.popSymbole());
            Symbole* op = automate.popSymbole();
            delete op;
            Expr* gauche = dynamic_cast<Expr*>(automate.popSymbole());
            Expr* exprPlus = new ExprPlus(gauche, droite);
            automate.reduction(3, exprPlus);
            return true;
        }
        default:
            cerr << "Erreur de syntaxe (E7)" << endl;
            return false;
    }
}

// State 8: E -> E * E .  (always reduce rule 3)
// +->r3, *->r3, )->r3, $->r3
bool Etat8::transition(Automate& automate, Symbole* s) {
    switch (*s) {
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN: {
            // Reduce rule 3: E -> E * E
            Expr* droite = dynamic_cast<Expr*>(automate.popSymbole());
            Symbole* op = automate.popSymbole();
            delete op;
            Expr* gauche = dynamic_cast<Expr*>(automate.popSymbole());
            Expr* exprMult = new ExprMult(gauche, droite);
            automate.reduction(3, exprMult);
            return true;
        }
        default:
            cerr << "Erreur de syntaxe (E8)" << endl;
            return false;
    }
}

// State 9: E -> ( E ) .  (reduce rule 4)
// +->r4, *->r4, )->r4, $->r4
bool Etat9::transition(Automate& automate, Symbole* s) {
    switch (*s) {
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN: {
            // Reduce rule 4: E -> ( E )
            Symbole* closePar = automate.popSymbole();
            delete closePar;
            Expr* expr = dynamic_cast<Expr*>(automate.popSymbole());
            Symbole* openPar = automate.popSymbole();
            delete openPar;
            automate.reduction(3, expr);
            return true;
        }
        default:
            cerr << "Erreur de syntaxe (E9)" << endl;
            return false;
    }
}
