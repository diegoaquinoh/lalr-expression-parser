#include "symbole.h"
#include <iostream>

void Symbole::Affiche() {
   cout<<Etiquettes[ident];
}

void Entier::Affiche() {
   Symbole::Affiche();
   cout<<"("<<valeur<<")";
}

void Nombre::Affiche() {
   cout<<"EXPR(nombre="<<valeur<<")";
}

double ExprPlus::eval(const map<string, double> & valeurs) {
   return gauche->eval(valeurs) + droite->eval(valeurs);
}

double ExprMult::eval(const map<string, double> & valeurs) {
   return gauche->eval(valeurs) * droite->eval(valeurs);
}

double Nombre::eval(const map<string, double> & valeurs) {
   return (double)valeur;
}

