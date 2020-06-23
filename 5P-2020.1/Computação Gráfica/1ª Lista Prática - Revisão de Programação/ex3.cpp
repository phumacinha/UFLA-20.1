/**
    Objetivo: Calcular a intersecao de um segmento de reta com uma reta que
    pode ser vertical ou horizontal.

    @author Pedro Antônio de Souza
*/

#include <iostream>
using namespace std;

int main() {
    double x1, y1, x2, y2;
    char tipo_de_reta;
    double intersecao, resultado;

    cin >> x1 >> y1;
    cin >> x2 >> y2;

    cin >> tipo_de_reta;

    cin >> intersecao;

    if (tipo_de_reta == 'x') {
        if ((intersecao > x1 && intersecao > x2) || (intersecao < x1 && intersecao < x2)) {
            cout << "nenhuma" << endl;
            return 0;
        }
        resultado = (y2 - y1)*(intersecao - x1)/(x2 - x1) + y1;
    }
    else if (tipo_de_reta == 'y') {
        if ((intersecao > y1 && intersecao > y2) || (intersecao < y1 && intersecao < y2)) {
            cout << "nenhuma" << endl;
            return 0;
        }
        resultado = (x2 - x1)*(intersecao - y1)/(y2 - y1) + x1;
    }
    else
        return -1;

    cout << resultado << endl;

    return 0;
}