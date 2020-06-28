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
    const int INSIDE = 0; // 0000 
    const int LEFT = 1; // 0001 
    const int RIGHT = 2; // 0010 
    const int BOTTOM = 4; // 0100 
    const int TOP = 8; // 1000 

    const double newXmin = 0;
    const double newXmax = mXmax - mXmin;
    const double newYmin = 0;
    const double newYmax = mYmax - mYmin;

    const Point translacao(mXmin, mYmin);

    Point *P0 = l.mP0;
    Point *P1 = l.mP1;

    int code_P0 = INSIDE;
    int code_P1 = INSIDE;

    if (P0.mX < newXmin)
        code_P0 |= LEFT;
    else if (P0.mX > newXmax) // to the right of rectangle 
        code_P0 |= RIGHT; 
    if (P0.mY < newYmin) // below the rectangle 
        code_P0 |= BOTTOM; 
    else if (P0.mY > newYmax) // above the rectangle 
        code_P0 |= TOP;

    if (P1.mX < newXmin)
        code_P1 |= LEFT;
    else if (P1.mX > newXmax) // to the right of rectangle 
        code_P1 |= RIGHT; 
    if (P1.mY < newYmin) // below the rectangle 
        code_P1 |= BOTTOM; 
    else if (P1.mY > newYmax) // above the rectangle 
        code_P1 |= TOP; 


    bool linhaDentro = false;

    while (true) {
        if (code_P0 == 0 && code_P1 == 0) {
            linhaDentro = true;
            break;
        }
        else if (code_P0 && code_P1) {
            break;
        }
        else {
            int code_out;
            double x, y;

            if (code_P0 != 0) code_out = code_P0;
            else code_out = code_P1;


            if (code_out & TOP) {
                x = P0.mX + (P1.mX - P0.mx) * (newYmax - P0.mY) / (P1.mY - P0.mY);
                y = newYmax;
            }
            else if (code_out & BOTTOM) {
                x = P0.mX + (P1.mX - P0.mX) * (newYmin - P0.mY) / (P1.mY - P0.mY);
                y = newYmin;
            }
            else if (code_out & RIGHT) {
                y = P0.mY + (P1.mY - P0.mY) * (newXmax - P0.mX) / (P1.mX - P0.mX);
                x = newXmax;
            }
            else if (code_out & LEFT) {
                y = P0.mY + (P1.mY - P0.mY) * (newXmin - P0.mX) / (P1.mX - P0.mX);
                x = newXmin;
            }



            if (code_out == code_P0) { 
                P0.mX = x; 
                P0.mY = y;
            } 
            else { 
                P1.mX = x; 
                P2.mY = y;
            } 

            if (linhaDentro) return new Line(P0, P1);
            else return Line();
        }
    }

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


