#pragma once

#include <string>
#include <map>

using namespace std;

enum Identificateurs { EXPR, OPENPAR, CLOSEPAR, PLUS, MULT, INT, FIN, ERREUR };

const string Etiquettes[] = { "EXPR", "OPENPAR", "CLOSEPAR", "PLUS", "MULT", "INT", "FIN", "ERREUR" };

class Symbole {
   public:
      Symbole(int i) : ident(i) {  }
      virtual ~Symbole() { }
      operator int() const { return ident; }
      virtual void Affiche();

   protected:
      int ident;
};

class Expr : public Symbole {
public:
   Expr():Symbole(EXPR) {}
   virtual~Expr() {}
   virtual double eval(const map<string, double> & valeurs) = 0;
};

class Entier : public Symbole {
   public:
      Entier(int v) : Symbole(INT), valeur(v) { }
      ~Entier() { }
      virtual void Affiche();
   protected:
      int valeur;
};
