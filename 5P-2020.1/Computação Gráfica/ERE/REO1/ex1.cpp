#include <iostream>
#include <cmath>
#include <typeinfo>
#include <vector>

using namespace std;
/*******************************************************************************
 * Classe Matriz que implementa operações entre matrizes através de sobrecarga
 * de operadores, métodos de inserção e alteração de elementos e método de
 * impressão.
*******************************************************************************/
class Matriz {
    public:
        Matriz();
        Matriz(int num_linhas, int num_colunas);
        Matriz(int num_linhas, int num_colunas, vector<double> elems);
        ~Matriz();
        int get_num_linhas() const;
        int get_num_colunas() const;
        double get_elem_pos(int i, int j) const;
        void insere_elemento_pos(int i, int j, double elem);
        void insere_elementos(vector<double> elems);
        void imprimir() const;
        vector<double> to_vector();

        template <class T> 
        T operator*(const T &) const;

        bool operator==(const Matriz &) const;
        Matriz operator*(double x) const;
        void operator=(const Matriz &);

        template <class T> 
        T operator-(const T &) const;

        template <class T>
        T operator+(const T &) const;

        static Matriz matriz_identidade (int n);
    
    private:
        vector<vector<double>> matriz; //double **matriz;
        int num_linhas=0, num_colunas=0;

        void iniciar_matriz(int num_linhas, int num_colunas);
        void desaloca_matriz();
};

Matriz::Matriz() {
    iniciar_matriz(0,0);
}

Matriz::Matriz(int num_linhas, int num_colunas) {
    iniciar_matriz(num_linhas, num_colunas);
}

Matriz::Matriz(int num_linhas, int num_colunas, vector<double> elems) {
    iniciar_matriz(num_linhas, num_colunas);
    insere_elementos(elems);
}

void Matriz::iniciar_matriz(int num_linhas, int num_colunas) {
    desaloca_matriz();
    matriz.assign(num_linhas, vector<double>(num_colunas));
    this->num_linhas = num_linhas;
    this->num_colunas = num_colunas;
}

Matriz::~Matriz() {
    desaloca_matriz();
}

void Matriz::desaloca_matriz() {
    matriz.clear();
}

int Matriz::get_num_linhas() const {
    return num_linhas;
}

int Matriz::get_num_colunas() const {
    return num_colunas;
}

double Matriz::get_elem_pos(int i, int j) const {
    return matriz[i][j];
}

void Matriz::insere_elemento_pos(int i, int j, double elem) {
    matriz[i][j] = elem;
}

void Matriz::insere_elementos(vector<double> elems) {
    for (int i=0; i<get_num_linhas(); i++){
        for (int j=0; j<get_num_colunas(); j++){
            int indice_elem = i*get_num_colunas() + j;
            insere_elemento_pos(i, j, elems[indice_elem]);
        }
    }
}

void Matriz::imprimir() const {
    for (int i=0; i<get_num_linhas(); i++) {
        for (int j=0; j<get_num_colunas(); j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

bool Matriz::operator==(const Matriz & outra_matriz) const{
    bool eh_igual = (get_num_linhas() == outra_matriz.get_num_linhas()) && (get_num_colunas() == outra_matriz.get_num_colunas());

    if (eh_igual) {
        for (int i=0; i<get_num_linhas(); i++) {
            for (int j=0; j<get_num_colunas(); j++) {
                eh_igual = this->get_elem_pos(i, j) == outra_matriz.get_elem_pos(i, j);
                if (!eh_igual) break;
            }
            if (!eh_igual) break;
        }
    }

    return eh_igual;
}

template <class T> 
T Matriz::operator-(const T &outra_matriz) const {
    int m = get_num_linhas();
    int n = get_num_colunas();
    T resultado;
    resultado.iniciar_matriz(m, n);

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            double elem = get_elem_pos(i,j) - outra_matriz.get_elem_pos(i,j);
            resultado.insere_elemento_pos(i, j, elem);
        }
    }

    return resultado;
}

template <class T> 
T Matriz::operator+(const T &outra_matriz) const {
    int m = get_num_linhas();
    int n = get_num_colunas();
    T resultado;
    resultado.iniciar_matriz(m, n);

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            double elem = this->get_elem_pos(i,j) + outra_matriz.get_elem_pos(i,j);
            resultado.insere_elemento_pos(i, j, elem);
        }
    }

    return resultado;
}

template <class T> 
T Matriz::operator*(const T &outra_matriz) const {
    int n = get_num_colunas();
    int novo_num_linhas = get_num_linhas();
    int novo_num_colunas = outra_matriz.get_num_colunas();
    T nova_matriz;
    nova_matriz.iniciar_matriz(novo_num_linhas, novo_num_colunas);

    double resultado;
    for (int i=0; i<novo_num_linhas; i++) {
        for (int j=0; j<novo_num_colunas; j++) {
            resultado = 0;
            for (int k=0; k<n; k++) {
                resultado += get_elem_pos(i, k) * outra_matriz.get_elem_pos(k, j);
            }

            nova_matriz.insere_elemento_pos(i, j, resultado);
        }
    }

    return nova_matriz;
}

void Matriz::operator=(const Matriz &outra_matriz) {
    int m = outra_matriz.get_num_linhas();
    int n = outra_matriz.get_num_colunas();
    vector<double> elems;

    for (int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            elems.push_back(outra_matriz.get_elem_pos(i, j));
        }
    }

    iniciar_matriz(m,n);
    insere_elementos(elems);
}

Matriz Matriz::operator*(double x) const {
    int m = this->get_num_linhas();
    int n = this->get_num_colunas();
    Matriz nova_matriz;
    nova_matriz.iniciar_matriz(m,n);

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {

            nova_matriz.insere_elemento_pos(i, j, this->get_elem_pos(i, j)*x);
        }
    }

    return nova_matriz;
}

Matriz Matriz::matriz_identidade (int n) {
    Matriz identidade(n, n);
    
    double elem;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            elem = (i == j) ? 1 : 0;
            identidade.insere_elemento_pos(i, j, elem);
        }
    }

    return identidade;
}

vector<double> Matriz::to_vector() {
    vector<double> vetor;
    for (int i=0; i<get_num_linhas(); i++) {
        for (int j=0; j<get_num_colunas(); j++) {
            vetor.push_back(get_elem_pos(i,j));
        }
    }
    return vetor;
}






class Elemento : public Matriz {
    public:
        Elemento() : Matriz(4,1) {}
        Elemento(vector<double> coords);
        Elemento(double x, double y, double z, double w);
        Elemento(double x, double y, double z);
        double get_coord(int pos) const;
        double get_coord(char coord) const;
        void altera_coord(int pos, double valor);
        void altera_coord(char coord, double valor);
        void converte_tipo(Elemento elem);
    private:
        void inicializa_coordenadas(vector<double> coords);
        int id_coord(char coord) const;
};

Elemento::Elemento(vector<double> coords) : Matriz(4,1) {
    inicializa_coordenadas(coords);
}

Elemento::Elemento(double x, double y, double z, double w) : Matriz(4,1) {
    vector<double> coords;
    coords.push_back(x);
    coords.push_back(y);
    coords.push_back(z);
    coords.push_back(w);
    inicializa_coordenadas(coords);
}

Elemento::Elemento(double x, double y, double z) : Matriz(4,1) {
    vector<double> coords;
    coords.push_back(x);
    coords.push_back(y);
    coords.push_back(z);
    inicializa_coordenadas(coords);
}

void Elemento::inicializa_coordenadas(vector<double> coords) {
    int comprimento_param = coords.size();
    
    for (int i=0; i<comprimento_param; i++) {
        altera_coord(i, coords[i]);
    }
}

int Elemento::id_coord(char coord) const {
    switch (coord) {
        case 'x': return 0;
        case 'y': return 1;
        case 'z': return 2;
        case 'w': return 3;
    }

    return -1;
}

double Elemento::get_coord(int pos) const {
    return get_elem_pos(pos, 0);
}

double Elemento::get_coord(char coord) const {
    return get_elem_pos(id_coord(coord), 0);
}

void Elemento::altera_coord(int pos, double valor) {
    insere_elemento_pos(pos, 0, valor);
}

void Elemento::altera_coord(char coord, double valor) {
    insere_elemento_pos(id_coord(coord), 0, valor);
}

void Elemento::converte_tipo(Elemento elem) {
    inicializa_coordenadas(elem.to_vector());
}




class Ponto : public Elemento {
    public:
        Ponto() : Elemento() {}
        Ponto(vector<double> coords);
        Ponto(double x, double y, double z, double w);
        Ponto(double x, double y, double z);
        Ponto operator-(const Ponto &) const;
        Ponto operator+(const Ponto &) const;
        void operator=(Elemento & elem);
};

Ponto::Ponto(double x, double y, double z, double w) : Elemento(x, y, z, w) {
    if (w != 1) {
        double fator = 1/w;
        altera_coord(0, x*fator); 
        altera_coord(1, y*fator); 
        altera_coord(2, z*fator); 
        altera_coord(3, w*fator); 
    }

}

Ponto::Ponto(vector<double> coords) : Elemento(coords) {
    int comprimento_param = coords.size();

    if (comprimento_param == 4 && coords[3] != 1) {
        double fator = 1/coords[3];
        altera_coord(0, coords[0]*fator); 
        altera_coord(1, coords[1]*fator); 
        altera_coord(2, coords[2]*fator); 
        altera_coord(3, coords[3]*fator);
    }

    if (comprimento_param == 3) {
        insere_elemento_pos(3, 0, 1);
    }
}

Ponto::Ponto(double x, double y, double z) : Elemento(x, y, z) {
    insere_elemento_pos(3, 0, 1);
}

Ponto Ponto::operator-(const Ponto & outro_ponto) const {
    vector<double> novas_coords;

    for (int i=0; i<3; i++) {
        novas_coords.push_back(get_coord(i) - outro_ponto.get_coord(i));
    }

    return Ponto(novas_coords);
}

Ponto Ponto::operator+(const Ponto & outro_ponto) const {
    vector<double> novas_coords;

    for (int i=0; i<3; i++) {
        novas_coords.push_back(get_coord(i) + outro_ponto.get_coord(i));
    }

    return Ponto(novas_coords);
}

void Ponto::operator=(Elemento & elem) {
    for (int i=0; i<4; i++) {
        altera_coord(i, elem.get_coord(i));
    }
}



class Vetor : public Elemento {
    public:
        Vetor() : Elemento() {}
        Vetor(vector<double> coords) : Elemento(coords) {}
        Vetor(double x, double y, double z) : Elemento(x, y, z, 0) {}
        double get_comprimento() const;
        void normalizar();
        static double produto_escalar(Vetor & v1, Vetor & v2);
        template <class T>
        static double angulo_entre_vetores(Vetor & v1, T & v2);
        void operator=(Elemento & elem);
};

double Vetor::get_comprimento() const {
    return sqrt(pow(get_coord(0), 2) + pow(get_coord(1), 2) + pow(get_coord(2), 2));
}

void Vetor::normalizar() {
    for (int i=0; i<3; i++) {
        altera_coord(i, get_coord(i)/get_comprimento());
    }
}

double Vetor::produto_escalar(Vetor & v1, Vetor & v2) {
    double produto = 0;
    for (int i=0; i<3; i++) {
        produto += v1.get_coord(i)*v2.get_coord(i);
    }
    return produto;
}

template <class T>
double Vetor::angulo_entre_vetores(Vetor & v1, T & v2) {
    return acos(Vetor::produto_escalar(v1, v2)/(v1.get_comprimento() * v2.get_comprimento()));
}

void Vetor::operator=(Elemento & elem) {
    for (int i=0; i<4; i++) {
        altera_coord(i, elem.get_coord(i));
    }
}




class Transformacao {
    public:
        static Matriz translacao(vector<double> fatores);
        static Matriz rotacao(double angulo, char plano);
        static Matriz escala(double fatores[3]);
        static Matriz cisalhamento(double fatores[2], char dimensao_fixa);
        static const Ponto ORIGEM_SCM;
        static const Vetor EIXO_X;
        static const Vetor EIXO_Y;
        static const Vetor EIXO_Z;
    
    private:
        const Ponto CENTRO = Ponto(0,0,0);
        static Matriz matriz_identidade();
};

const Ponto Transformacao::ORIGEM_SCM = Ponto(0,0,0);
const Vetor Transformacao::EIXO_X = Vetor(1,0,0);
const Vetor Transformacao::EIXO_Y = Vetor(0,1,0);
const Vetor Transformacao::EIXO_Z = Vetor(0,0,1);

Matriz Transformacao::matriz_identidade() {
    return Matriz::matriz_identidade(4);
}

Matriz Transformacao::translacao(vector<double> fatores) {
    Matriz matriz_translacao = matriz_identidade();
    
    for (int i=0; i<3; i++) {
        matriz_translacao.insere_elemento_pos(i, 3, fatores[i]);
    }
    
    return matriz_translacao;
}

Matriz Transformacao::rotacao(double angulo, char eixo) {
    Matriz matriz_rotacao = matriz_identidade();

    int pos = -1;
    if (eixo == 'z') pos = 0;
    else if (eixo == 'x') pos = 1;
    else if (eixo == 'y') pos = 2;
    
    matriz_rotacao.insere_elemento_pos(pos, pos, cos(angulo));
    matriz_rotacao.insere_elemento_pos(pos, (pos+1)%3, -sin(angulo));

    matriz_rotacao.insere_elemento_pos((pos+1)%3, pos, sin(angulo));
    matriz_rotacao.insere_elemento_pos((pos+1)%3, (pos+1)%3, cos(angulo));


    return matriz_rotacao;
}

Matriz Transformacao::escala(double fatores[3]) {
    Matriz matriz_escala = matriz_identidade();

    for (int i=0; i<3; i++) {
        matriz_escala.insere_elemento_pos(i, i, fatores[i]);
    }

    return matriz_escala;
}

Matriz Transformacao::cisalhamento(double fatores[2], char dimensao_fixa){
    Matriz cisalhamento = matriz_identidade();
    
    int pos = -1;
    if (dimensao_fixa == 'x') pos = 0;
    else if (dimensao_fixa == 'y') pos = 1;
    else if (dimensao_fixa == 'z') pos = 2;

    int indice_fator = 0;
    for (int i=0; i<3; i++) {
        if (i != pos) {
            cisalhamento.insere_elemento_pos(i, pos, fatores[indice_fator]);
            indice_fator++;
        }
    }

    return cisalhamento;
}




class Projecao {
    public:
       Projecao(Ponto origem, Vetor eixo_x, Vetor eixo_y, Elemento centro_dir_projecao);
       Matriz matriz_projecao();

    private:
        Ponto origem;
        Vetor eixo_x, eixo_y;
        Elemento centro_dir_projecao;
        bool eh_paralela, eh_perspectiva;

        Matriz matriz_projecao_paralela();
        Matriz matriz_projecao_perspectiva();
};

Projecao::Projecao(Ponto origem, Vetor eixo_x, Vetor eixo_y, Elemento centro_dir_projecao) {
    this->origem = origem;
    this->eixo_x = eixo_x;
    this->eixo_y = eixo_y;
    this->centro_dir_projecao = centro_dir_projecao;

    this->eh_paralela = centro_dir_projecao.get_coord('w') == 0;
    this->eh_perspectiva = !this->eh_paralela;
}

Matriz Projecao::matriz_projecao() {
    return (eh_paralela) ? matriz_projecao_paralela() : matriz_projecao_perspectiva();
}

Matriz Projecao::matriz_projecao_paralela() {
    Matriz matriz_projecao;
    Vetor dir_projecao, vetor_aux;
    dir_projecao = centro_dir_projecao;
   
    // Translacao que leva a origem do PP na origem do SCM.
    matriz_projecao = Transformacao::translacao((Transformacao::ORIGEM_SCM - origem).to_vector());
    
    // Rotacao no eixo Y, em torno da origem (relativa a SCM) que leva a direcao de X do PP no plano XY do SCM.
    Vetor eixo_x_scm(1,0,0);
    Vetor eixo_y_scm(0,1,0);
    Vetor eixo_z_scm(0,0,1);

    vetor_aux = eixo_x;
    vetor_aux.altera_coord(1, 0);
    double angulo = Vetor::angulo_entre_vetores(eixo_x_scm, vetor_aux);

    Matriz rotacao_y = Transformacao::rotacao(angulo, 'y');
    eixo_x = rotacao_y*eixo_x;
    eixo_y = rotacao_y*eixo_y;
    dir_projecao = rotacao_y*dir_projecao;
    matriz_projecao = matriz_projecao*rotacao_y;
   
    // Rotação no eixo Z, em torno da origem (relativa a SCM) que leva a direção de X  do PP a coincidir com a direção de X do SCM.
    angulo = Vetor::angulo_entre_vetores(eixo_x_scm, eixo_x);
    Matriz rotacao_z = Transformacao::rotacao(angulo, 'z');
    eixo_x = rotacao_z*eixo_x;
    eixo_y = rotacao_z*eixo_y;
    dir_projecao = rotacao_z*dir_projecao;
    matriz_projecao = matriz_projecao*rotacao_z;
 
    // Rotação no eixo X, em torno da origem (relativa a SCM) que leva a direção de Y  do PP a coincidir com a direção de Y do SCM.
    if (Vetor::angulo_entre_vetores(eixo_y_scm, eixo_y) != 0) {
        cout << "aqu";
        vetor_aux = eixo_y;
        vetor_aux.altera_coord(1, 0);
        angulo = Vetor::angulo_entre_vetores(eixo_x_scm, vetor_aux);
        Matriz rotacao_x = Transformacao::rotacao(angulo, 'x');
        eixo_y = rotacao_x*eixo_y;
        dir_projecao = rotacao_x*dir_projecao;
        matriz_projecao = matriz_projecao*rotacao_x;
    }
    //É feita uma inclinação em X e Y em relação a Z para que a direção de projeção ficasse paralela ao eixo Z do SCM.
    double sh_x=0, sh_y=0;

    // Em X
    vetor_aux = dir_projecao;
    vetor_aux.altera_coord(1, 0);
    if (Vetor::angulo_entre_vetores(eixo_z_scm, vetor_aux) != 0) {
        angulo = Vetor::angulo_entre_vetores(eixo_z_scm, vetor_aux);
        sh_x = 1/tan(angulo);
    }

    // Em Y
    vetor_aux = dir_projecao;
    vetor_aux.altera_coord(0, 0);
    if (Vetor::angulo_entre_vetores(eixo_z_scm, vetor_aux) != 0) {
        angulo = Vetor::angulo_entre_vetores(eixo_z_scm, vetor_aux);
        sh_y = 1/tan(angulo);
    }

    Matriz cisalhamento = Transformacao::cisalhamento(new double[2]{sh_x, sh_y}, 'z');
    matriz_projecao = matriz_projecao*cisalhamento;

    return matriz_projecao;
}

Matriz Projecao::matriz_projecao_perspectiva() {
    Ponto centro_de_projecao;
    centro_de_projecao.converte_tipo(this->centro_dir_projecao);
    Vetor vetor_aux;
    Matriz matriz_projecao;
   
    // Translacao que leva a origem do PP na origem do SCM.
    matriz_projecao = Transformacao::translacao((Transformacao::ORIGEM_SCM - centro_de_projecao).to_vector());

    // Rotacao no eixo Y, em torno da origem (relativa a SCM) que leva a direcao de X do PP no plano XY do SCM.
    Vetor eixo_x_scm(1,0,0);
    Vetor eixo_y_scm(0,1,0);
    Vetor eixo_z_scm(0,0,1);

    vetor_aux = eixo_x;
    vetor_aux.altera_coord(1, 0);
    double angulo = Vetor::angulo_entre_vetores(eixo_x_scm, vetor_aux);

    Matriz rotacao_y = Transformacao::rotacao(angulo, 'y');
    eixo_x = rotacao_y*eixo_x;
    eixo_y = rotacao_y*eixo_y;
    matriz_projecao = matriz_projecao*rotacao_y;
   
    // Rotação no eixo Z, em torno da origem (relativa a SCM) que leva a direção de X  do PP a coincidir com a direção de X do SCM.
    angulo = Vetor::angulo_entre_vetores(eixo_x_scm, eixo_x);
    Matriz rotacao_z = Transformacao::rotacao(angulo, 'z');
    eixo_x = rotacao_z*eixo_x;
    eixo_y = rotacao_z*eixo_y;
    matriz_projecao = matriz_projecao*rotacao_z;
 
    // Rotação no eixo X, em torno da origem (relativa a SCM) que leva a direção de Y  do PP a coincidir com a direção de Y do SCM.
    if (Vetor::angulo_entre_vetores(eixo_y_scm, eixo_y) != 0) {
        cout << "aqu";
        vetor_aux = eixo_y;
        vetor_aux.altera_coord(1, 0);
        angulo = Vetor::angulo_entre_vetores(eixo_x_scm, vetor_aux);
        Matriz rotacao_x = Transformacao::rotacao(angulo, 'x');
        eixo_y = rotacao_x*eixo_y;
        matriz_projecao = matriz_projecao*rotacao_x;
    }


    //É feita uma inclinação em X e Y em relação a Z para que a direção de projeção ficasse paralela ao eixo Z do SCM.
    double sh_x=0, sh_y=0;

    // Em X
    vetor_aux = eixo_z_scm;
    vetor_aux.altera_coord(1, 0);
    if (Vetor::angulo_entre_vetores(eixo_z_scm, vetor_aux) != 0) {
        angulo = Vetor::angulo_entre_vetores(eixo_z_scm, vetor_aux);
        sh_x = 1/tan(angulo);
    }

    // Em Y
    vetor_aux = eixo_z_scm;
    vetor_aux.altera_coord(0, 0);
    if (Vetor::angulo_entre_vetores(eixo_z_scm, vetor_aux) != 0) {
        angulo = Vetor::angulo_entre_vetores(eixo_z_scm, vetor_aux);
        sh_y = 1/tan(angulo);
    }

    Matriz cisalhamento = Transformacao::cisalhamento(new double[2]{sh_x, sh_y}, 'z');
    matriz_projecao = matriz_projecao*cisalhamento;

    return matriz_projecao;
}



int main () {
    vector<double> coords_origem_pp, direcao_x_pp, direcao_y_pp, centro_dir;
    int i;
    double n;

    for (i=0; i<3; i++) {
        cin >> n;
        coords_origem_pp.push_back(n);
    }

    for (i=0; i<3; i++) {
        cin >> n;
        direcao_x_pp.push_back(n);
    }

    for (i=0; i<3; i++) {
        cin >> n;
        direcao_y_pp.push_back(n);
    }

    for (i=0; i<4; i++) {
        cin >> n;
        centro_dir.push_back(n);
    }

    Ponto origem_pp(coords_origem_pp);
    Vetor eixo_x(direcao_x_pp);
    Vetor eixo_y(direcao_y_pp);
    Elemento centro_dir_projecao(centro_dir);
    Projecao plano_projecao(origem_pp, eixo_x, eixo_y, centro_dir_projecao);
    cout << endl;
    plano_projecao.matriz_projecao().imprimir();
}

/*
0 0 0
0.707106781 0 0.707106781
0 1 0
0.707106781 0 -0.707106781 0

0 0 0
1 0 0
0 1 0
0 0 1 0
*/