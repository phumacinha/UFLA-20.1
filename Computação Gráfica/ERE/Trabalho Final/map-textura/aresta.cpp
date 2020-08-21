// (C) Pedro Antonio de Souza - DCC / UFLA - A divulgacao deste codigo e' proibida.

#include "aresta.h"

Aresta::Aresta(Vertice v, Vertice u) {
        if (v.pos.Y() < u.pos.Y()) {
            vertice1 = v;
            vertice2 = u;
        }
        else {
            vertice1 = u;
            vertice2 = v;
        }
        
}

// Sobre carga do operador < para verificar se uma aresta
// esta' a esquerda de outra aresta.
bool Aresta::operator<(const Aresta& a2) const {
    if (X1() == a2.X2() && Y1() == a2.Y1())
        return XdeY(Y1() + 1) < a2.XdeY(Y1() + 1);
    else
        return XdeY(Y2() - 1) < a2.XdeY(Y2() - 1);
}
                                                                                                                                                                                 // (C) Pedro Antonio de Souza - Não é permitido divulgar esta implementação - Publishing this code is forbidden
