/**
    Objetivo: Multiplicar duas matrizes 4x4 utilizando sobrecarga de operador.

    @author Pedro Antônio de Souza
*/

#include <iostream>
#include <iomanip>
#include <array>
using namespace std;

class Matriz {
    array<array<float, 4>, 4> matriz;
    
    public:
        Matriz();
        Matriz(array<array<float, 4>, 4> matriz);
        void preencher_matriz();
        void show();
        array<array<float, 4>, 4> get_matriz();
        Matriz operator*(Matriz m2);
};

Matriz::Matriz () {
    this->preencher_matriz();
}

Matriz::Matriz(array<array<float, 4>, 4> matriz) {
    this->matriz = matriz;
}

void Matriz::preencher_matriz () {
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            cin >> matriz[i][j];
        }
    }
}

array<array<float, 4>, 4> Matriz::get_matriz () {
    return matriz;
}

Matriz Matriz::operator*(Matriz m2){

    array<array<float, 4>, 4> m1 = matriz;
    array<array<float, 4>, 4> produto;

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            produto[i][j] = 0;
        }
    }

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            for (int k=0; k<4; k++) {
                produto[i][j] = produto[i][j] + m1[i][k]*m2.get_matriz()[k][j];
            }
        }
    }

    return Matriz(produto);
}

void Matriz::show () {
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            cout << fixed << setprecision(6) << this->matriz[i][j] << " ";
        }
        cout << endl;
    }
}

int main () {
    Matriz m1, m2;
    cout << endl;
    cout << endl;

    Matriz m3 = m1*m2;

    m3.show();

    return 0;
}