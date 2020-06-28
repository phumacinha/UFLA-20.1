#include "clip-rectangle.h"
#include <iostream>
#include <cmath>

using namespace std;

ClipRectangle::ClipRectangle (double xmin, double xmax, double ymin, double ymax)
    : mXmin(xmin), mXmax(xmax), mYmin(ymin), mYmax(ymax), mInitialized(true) 
{}

void ClipRectangle::Set(double xmin, double xmax, double ymin, double ymax)
{
    mXmin = xmin;
    mXmax = xmax;
    mYmin = ymin;
    mYmax = ymax;
    mInitialized = true;
}

// Retorna um ponteiro para uma linha recem alocada inteiramente dentro da area de recorte
// ou NULL se l for completamente descartada.
// A linha alocada aqui será desalocada na função CleanUp().
Line* ClipRectangle::Clip(const Line& l)
{
    Point P0 = l.mP0;
    Point P1 = l.mP1;

    int code_P0 = PositionCode(P0);
    int code_P1 = PositionCode(P1);

    while (true) {
        // Se os dois pontos possuem codigo zero, ambos estao dentro da area de recorte.
        if (!(code_P0 | code_P1)) {
            return new Line(P0, P1);
        }
        // Se os codigos dos dois pontos possuem um bit 1 na mesma posicao, a
        // linha toda esta fora da area de recorte.
        else if (code_P0 & code_P1) {
            return new Line();
        }
        else {
            int code;
            double x, y;

            // Seleciona o ponto com maior diferenca de 0, ou seja, com mais intersecoes.
            code = code_P0 > code_P1 ? code_P0 : code_P1;

            // Verifica com qual lado do retangulo de recorte ha intersecao e calcula
            // o ponto de intersecao utilizando semelhanca de triangulos.
            if (code & TOP) {
                x = P0.mX + (P1.mX - P0.mX) * (mYmax - P0.mY) / (P1.mY - P0.mY);
                y = mYmax;
            }
            else if (code & BOTTOM) {
                x = P0.mX + (P1.mX - P0.mX) * (mYmin - P0.mY) / (P1.mY - P0.mY);
                y = mYmin;
            }
            else if (code & RIGHT) {
                y = P0.mY + (P1.mY - P0.mY) * (mXmax - P0.mX) / (P1.mX - P0.mX);
                x = mXmax;
            }
            else if (code & LEFT) {
                y = P0.mY + (P1.mY - P0.mY) * (mXmin - P0.mX) / (P1.mX - P0.mX);
                x = mXmin;
            }


            // Atuliza pontos
            if (code == code_P0) { 
                P0.mX = x; 
                P0.mY = y;
                code_P0 = PositionCode(P0);
            } 
            else { 
                P1.mX = x; 
                P1.mY = y;
                code_P1 = PositionCode(P1);
            }
        }
    }
}

// Retorna o codigo de localizacao de um ponto.
int ClipRectangle::PositionCode(const Point &P) {
    int code = INSIDE;

    if (P.mX < mXmin) code |= LEFT;
    else if (P.mX > mXmax) code |= RIGHT; 

    if (P.mY < mYmin) code |= BOTTOM; 
    else if (P.mY > mYmax)  code |= TOP;

    return code;
}

void ClipRectangle::Read(const string& prompt)
{
    cout << prompt;
    cin >> mXmin >> mXmax >> mYmin >> mYmax;
    if (not mInitialized)
        mInitialized = true;
}

ostream& operator << (ostream& os, const ClipRectangle& r)
{
    return os << "(Clipping Rectangle: " << r.mXmin << ", " << r.mXmax << ", " 
              << r.mYmin << ", " << r.mYmax << ")";
}


