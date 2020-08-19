// Classe Aresta pra programas de mapeamento de textura
// (C) Pedro Antonio de Souza - Agosto de 2020

#ifndef ARESTA_H
#define ARESTA_H

#include "vertice.h"

class Aresta {
    public:
        Aresta(Vertice v, Vertice u);

        inline double X1() const { return vertice1.pos.X(); }
        inline double Y1() const { return vertice1.pos.Y(); }
        inline double Z1() const { return vertice1.pos.Z(); }
        inline double U1() const { return vertice1.tex.u; }
        inline double V1() const { return vertice1.tex.v; }

        inline double X2() const { return vertice2.pos.X(); }
        inline double Y2() const { return vertice2.pos.Y(); }
        inline double Z2() const { return vertice2.pos.Z(); }
        inline double U2() const { return vertice2.tex.u; }
        inline double V2() const { return vertice2.tex.v; }

        double XdeY (double y) const { return X1() + (X2() - X1())*(y - Y1())/(Y2() - Y1()); }
        double ZdeY (double y) const { return Z1() + (Z2() - Z1())*(y - Y1())/(Y2() - Y1()); }
        double UdeY (double y) const { return U1() + (U2() - U1())*(y - Y1())/(Y2() - Y1()); }
        double VdeY (double y) const { return V1() + (V2() - V1())*(y - Y1())/(Y2() - Y1()); }
        double Ydif () const { return Y2() - Y1(); }
        double Xdif () const { return X2() - X1(); }

        bool operator<(const Aresta& a) const;

    private:
        Vertice vertice1;
        Vertice vertice2;
};

#endif
                                                                                                                                                                                 // (C) Pedro Antonio de Souza - Não é permitido divulgar esta implementação - Publishing this code is forbidden
