/**
    Objetivo: Encontrar as coordenadas de cada cadeira de uma roda gigante
        sabendo que o centro da roda fica na origem do sistema de coordenadas.

    @author Pedro Antônio de Souza
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

#define PI 3.14159265358

int main() {
    double raio;
    int quantidade_de_cadeiras;

    cin >> raio >> quantidade_de_cadeiras;

    double angulo = 2*PI/(double)quantidade_de_cadeiras;
    double x, y;

    for (int i=0; i<quantidade_de_cadeiras; i++) {
        x = cos(angulo*i)*raio;
        y = sin(angulo*i)*raio;

        cout << fixed << setprecision(2) << x << " " << y << endl;
    }

    return 0;
}