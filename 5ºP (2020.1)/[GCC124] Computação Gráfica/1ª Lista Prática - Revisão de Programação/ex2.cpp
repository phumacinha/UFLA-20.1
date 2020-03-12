/**
    Objetivo: Dadas, respectivamente a largura e a altura da janela, além das
    coordenadas do mouse, calcular e escrever as coordenadas que representam
    a posição do mouse conforme as coordenadas dos dados.

    @author Pedro Antônio de Souza
*/

#include <iostream>
using namespace std;

int main() {
    int largura_da_janela, altura_da_janela;
    int mouse_x, mouse_y;

    cin >> largura_da_janela >> altura_da_janela;
    cin >> mouse_x >> mouse_y;

    double coord_x, coord_y;

    coord_x = (double)(mouse_x - largura_da_janela/2)/(largura_da_janela/2);
    coord_y = (double)(altura_da_janela/2 - mouse_y)/(altura_da_janela/2);

    cout << coord_x << endl << coord_y << endl;

   

    return 0;
}