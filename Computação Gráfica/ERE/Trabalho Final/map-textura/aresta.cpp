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

bool Aresta::operator<(const Aresta& a2) const {
    double minXa1 = std::min(X1(), X2());
    double minXa2 = std::min(a2.X1(), a2.X2());
    
    if (minXa1 == minXa2)
        return std::max(X1(), X2()) < std::max(a2.X1(), a2.X2());

    return minXa1 < minXa2;
}
                                                                                                                                                                                 // (C) Pedro Antonio de Souza - Não é permitido divulgar esta implementação - Publishing this code is forbidden
