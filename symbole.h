#pragma once

#include <string>
#include <map>
#include <cassert>

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

class SymboleSimple : public Symbole {
public:
   SymboleSimple(int i) : Symbole(i) {
      assert(i == OPENPAR || i == CLOSEPAR || i == PLUS || i == MULT || i == FIN);
   }
   ~SymboleSimple() { }
};

class Expr : public Symbole {
public:
   Expr():Symbole(EXPR) {}
   virtual~Expr() {}
   virtual double eval(const map<string, double> & valeurs) = 0;
};


class ExprBin : public Expr {
   public:
      ExprBin(Expr * g, Expr * d) : Expr(), gauche(g), droite(d) { }
      ~ExprBin() { delete gauche; delete droite; }
   protected:   
      Expr * gauche;
      Expr * droite;
};

class ExprPlus : public ExprBin {
   public:
      ExprPlus(Expr * g, Expr * d) : ExprBin(g, d) { }
      ~ExprPlus() { }
      virtual double eval(const map<string, double> & valeurs);
};

class ExprMult : public ExprBin {
   public:
      ExprMult(Expr * g, Expr * d) : ExprBin(g, d) { }
      ~ExprMult() { }
      virtual double eval(const map<string, double> & valeurs);
};

class Nombre : public Expr {
   public:
      Nombre(int v) : Expr(), valeur(v) { }
      ~Nombre() { }
      virtual double eval(const map<string, double>& valeurs);
    
      virtual void Affiche();
   protected:
      int valeur;
};

class Entier : public Symbole {
   public:
      Entier(int v) : Symbole(INT), valeur(v) { }
      ~Entier() { }
      virtual void Affiche();
      int getValeur() const { return valeur; }
   protected:
      int valeur;
};

