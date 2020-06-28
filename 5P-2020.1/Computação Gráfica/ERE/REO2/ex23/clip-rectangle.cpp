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
    double newXmin = 0;
    double newXmax = mXmax - mXmin;
    double newYmin = 0;
    double newYmax = mYmax - mYmin;

    Point translacao(mXmin, mYmin);

    Line newLine(l.mP0-translacao, l.mP1-translacao);

    double posIni = 0;
    double posFim = 1;
    double denominador, numerador, t;

    // Iteracao para analisar todos os lados da area de recorte
    for (int i=0; i<4; i++) {
        switch (i) {
            // Lado esquerdo
            case 0:
                numerador = newXmin - newLine.mP0.mX;
                denominador = newLine.mP1.mX - newLine.mP0.mX;
                break;
            
            // Lado inferior:
            case 1:
                numerador = newYmin - newLine.mP0.mY;
                denominador = newLine.mP1.mY - newLine.mP0.mY;
                break;
            
            // Lado direito:
            case 2:
                numerador = newLine.mP0.mX - newXmax;
                denominador = newLine.mP0.mX - newLine.mP1.mX;
                break;
            
            // Lado superior:
            case 3:
                numerador = newLine.mP0.mY - newYmax;
                denominador = newLine.mP0.mY - newLine.mP1.mY;
                break;
        }


        // se for paralelo
        if (denominador == 0) {
            if (numerador > 0) return new Line();
        }
        else {
            t = numerador/denominador;

            // se esta potencialmente entrando
            if (denominador > 0) {
                if (t > posFim) return new Line();
                if (t > posIni) posIni = t;
            }

            // senao (esta potencialmente saindo)
            else {
                if (t < posIni) return new Line();
                if (t < posFim) posFim = t;
            }
        }
    }

    return new Line(l.Coordinates(posIni), l.Coordinates(posFim));
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


