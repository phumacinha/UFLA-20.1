/**
    Objetivo: Dados dois pontos de uma reta, calcular os coeficientes da equação reduzida.

    @author Pedro Antônio de Souza
*/

#include <iostream>
using namespace std;

int main() {
    double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    double m, q;
    
    m = (y2 - y1)/(x2 - x1);
    q = y1 - m*x1;

    cout << m << endl;
    cout << q << endl;

    return 0;
}