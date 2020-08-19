// Exemplo de mapeamento de texturas

// Criado por Bruno Schneider a partir do exemplo "cube.cpp" do wxWidgets.
// (C) Bruno Schneider - DCC / UFLA - Julho de 2017

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "main.h"
#include <iostream>

#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "icone.xpm"
#endif

#include <iomanip>

// IDs para os controles
enum {
    ID_SLIDER = wxID_HIGHEST + 1,
    ID_MAP_NAO_LINEAR
};

using namespace std;

// Converte Ponto para wxPoint
wxPoint WxPoint(const Ponto& v) {
    return wxPoint(v.X(), v.Y());
}

// Classe MyApp representa o programa
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    if ( !wxApp::OnInit() )
        return false;

    Janela* ptFrame = new Janela();
    ptFrame->AssociarTextura(&mTextura);
    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxJPEGHandler);
    return true;
}

int MyApp::OnExit() {
    return wxApp::OnExit();
}

// PainelDaTextura: Parte da janela onde será mostrada a textura e o usuário define as coordenadas
// de textura.

wxBEGIN_EVENT_TABLE(PainelDaTextura, wxPanel)
    EVT_PAINT(PainelDaTextura::OnPaint)
    EVT_COMMAND_SCROLL(ID_SLIDER, PainelDaTextura::QuandoMoverSlider)
wxEND_EVENT_TABLE()

PainelDaTextura::PainelDaTextura(wxWindow* ptMae)
    : wxPanel(ptMae, wxID_ANY, wxDefaultPosition, wxSize(256, -1)) {

    new wxSlider(this, ID_SLIDER, 45, 0, 60, wxPoint(0, 300), wxSize(256, 10));
}
void PainelDaTextura::AssociarPainelDesenho(PainelDoDesenho* ptPainel) {
    mPtPainelDesenho = ptPainel;
}

void PainelDaTextura::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    dc.DrawText(wxT("Textura:"), 5, 4);
    // Desenhar a textura com margem superior de 30 pixels
    dc.DrawBitmap(wxBitmap(*mPtTextura), 0, 30);
}
void PainelDaTextura::QuandoMoverSlider(wxScrollEvent& evento) {
    mPtPainelDesenho->AlterarRotatacao(evento.GetInt());
}


// PainelDoDesenho: Parte da janela onde será desenhado um poligono texturizado.

wxBEGIN_EVENT_TABLE(PainelDoDesenho, wxPanel)
    EVT_PAINT(PainelDoDesenho::OnPaint)
    EVT_SIZE(PainelDoDesenho::OnSize)
wxEND_EVENT_TABLE()

PainelDoDesenho::PainelDoDesenho(wxWindow* ptMae)
    : wxPanel(ptMae, wxID_ANY, wxDefaultPosition, wxDefaultSize),
      mVertices{ Ponto(-1, 0, 0), Ponto(-1, 1, 0), Ponto(1, 1, 0), Ponto(1, 0, 0) },
      mVetCoordTex{{0,1}, {0,0}, {1,0}, {1,1}},
      mPtMae(dynamic_cast<wxFrame*>(ptMae)),
      mMapeamentoNaoLinear(true)
{
    SetBackgroundColour(*wxBLACK);
    mRotacao.CarregarRotacaoX(M_PI_4);
    mPerspectiva.CarregarProjecaoPer(1);
    mAfastamento.CarregarTranslacao(0,0,1);
}

void PainelDoDesenho::AlterarRotatacao(int graus) {
    mRotacao.CarregarRotacaoX(graus*0.017453293);
    Refresh();
}

// Metodo para desenhar um triangulo com textura
void PainelDoDesenho::DesenharTriangulo(wxPaintDC* ptDC, Vertice v1, Vertice v2, Vertice v3) {
    if (mMapeamentoNaoLinear) {
    
        // Variaveis de gradiente
        double ginvzx, ginvzy, guinvzx, guinvzy, gvinvzx, gvinvzy;
        // Denominador do calculo de gradientes
        double denominador;

        denominador = ((v3.pos.X() - v2.pos.X()) * (v3.pos.Y() - v1.pos.Y()))
                    + ((v2.pos.Y() - v3.pos.Y()) * (v3.pos.X() - v1.pos.X()));

        // d(1/z)/dx
        ginvzx =  ((1/v3.pos.Z() - 1/v2.pos.Z()) * (v3.pos.Y() - v1.pos.Y()) +
                (v2.pos.Y() - v3.pos.Y()) * (1/v3.pos.Z() - 1/v1.pos.Z()))/denominador;

        // d(1/z)/dy
        ginvzy =  ((1/v2.pos.Z() - 1/v3.pos.Z()) * (v3.pos.X() - v1.pos.X()) +
                (v3.pos.X() - v2.pos.X()) * (1/v3.pos.Z() - 1/v1.pos.Z()))/denominador;

        // d(u/z)/dx
        guinvzx =  ((v3.tex.u/v3.pos.Z() - v2.tex.u/v2.pos.Z()) * (v3.pos.Y() - v1.pos.Y()) +
                (v2.pos.Y() - v3.pos.Y()) * (v3.tex.u/v3.pos.Z() - v1.tex.u/v1.pos.Z()))/denominador;

        // d(u/z)/dy
        guinvzy =  ((v2.tex.u/v2.pos.Z() - v3.tex.u/v3.pos.Z()) * (v3.pos.X() - v1.pos.X()) +
                (v3.pos.X() - v2.pos.X()) * (v3.tex.u/v3.pos.Z() - v1.tex.u/v1.pos.Z()))/denominador;

        // d(v/z)/dx
        gvinvzx =  ((v3.tex.v/v3.pos.Z() - v2.tex.v/v2.pos.Z()) * (v3.pos.Y() - v1.pos.Y()) +
                (v2.pos.Y() - v3.pos.Y()) * (v3.tex.v/v3.pos.Z() - v1.tex.v/v1.pos.Z()))/denominador;

        // d(v/z)/dy
        gvinvzy =  ((v2.tex.v/v2.pos.Z() - v3.tex.v/v3.pos.Z()) * (v3.pos.X() - v1.pos.X()) +
                (v3.pos.X() - v2.pos.X()) * (v3.tex.v/v3.pos.Z() - v1.tex.v/v1.pos.Z()))/denominador;

        // Instancia arestas
        Aresta arestas[3] = {{v1, v2}, {v2, v3}, {v3, v1}};
        
        double maiorVariacao = 0;
        int idArestaLonga = 0;

        // Verifica qual é a aresta longa (aquela que possui maior variacao no eixo Y)
        for (int i = 0; i < 3; i++) {
            double variacao = arestas[i].Y2() - arestas[i].Y1();
            if (variacao > maiorVariacao) {
                maiorVariacao = variacao;
                idArestaLonga = i;
            }
        }

        // Ponteiro para a aresta longa
        Aresta *arestaLonga = &arestas[idArestaLonga];

        // Desenha as duas metades do triangulo.
        for (int i = 1; i < 3; i++) {
            Aresta *arestaCurta = &arestas[(idArestaLonga + i) % 3];

            // Verifica se alguma das arestas e' paralela ao eixo X.
            if (arestaLonga->Ydif() == 0 || arestaCurta->Ydif() == 0)
                continue;

            // Como a classe Aresta define o vertice 1 como o vertice de menor Y,
            // e' facil calcular ymin e ymax. 
            double ymin = arestaCurta->Y1();
            double ymax = arestaCurta->Y2();
            
            // Ponteiros para a aresta 'a esquerda e 'a direita.
            bool longaEstaAesquerda = *arestaLonga < *arestaCurta;
            Aresta *arestaEsq = (longaEstaAesquerda) ? arestaLonga : arestaCurta;
            Aresta *arestaDir = (longaEstaAesquerda) ? arestaCurta : arestaLonga;

            // Calcula xesq e xdir baseado no ymin.
            double xesq = arestaEsq->XdeY(ymin);
            double xdir = arestaDir->XdeY(ymin);

            // Calcula o incremento da aresta esqueda e da direita.
            double incxesq = arestaEsq->Xdif()/arestaEsq->Ydif();
            double incxdir = arestaDir->Xdif()/arestaDir->Ydif();

            // Calcula caracteristicas a partir do menor y.
            double invz = (double)(1 / arestaEsq->ZdeY(ymin));
            double uinvz = (double)(arestaEsq->UdeY(ymin) * invz);
            double vinvz = (double)(arestaEsq->VdeY(ymin) * invz);

            wxPen pen(*wxBLUE_PEN);

            // Percorre todas as linhas, de baixo pra cima.
            for (int y = ymin; y <= ymax; y++) {
                
                // Percorre toda a linha de xesq ate' xdir na altura y desenhando cada pixel.
                for (int x = xesq; x <= xdir; x++) {
                    double difx = x - xesq;
                    double u = (uinvz + difx*guinvzx)/(invz + difx*ginvzx);
                    double v = (vinvz + difx*gvinvzx)/(invz + difx*ginvzx);

                    // Verifica se as coordenadas de textura sao validas.
                    // Se nao, parte para a proxima iteracao.
                    if (u < 0 || u > 1 || v < 0 || v > 1)
                        continue;

                    pen.SetColour(mPtTextura->ColourAt(u, v));
                    ptDC->SetPen(pen);
                    ptDC->DrawPoint(x, y);
                }

                // Incrementa xesq e xdir
                xesq += incxesq;
                xdir += incxdir;

                // Incrementa os gradientes.
                uinvz += guinvzx*incxesq + guinvzy;
                vinvz += gvinvzx*incxesq + gvinvzy;
                invz += ginvzx*incxesq + ginvzy;
            }
        }
    }
}

void PainelDoDesenho::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    Transformacao projecao = mTranslacao * mEscala * mPerspectiva * mAfastamento * mRotacao;
    Vertice vetVertices[4];
    for (int i = 0; i < 4; ++i) {
        vetVertices[i].pos = projecao * mVertices[i];
        vetVertices[i].tex = mVetCoordTex[i];
        vetVertices[i].ConverterParaPosicaoNaTela();
    }
    DesenharTriangulo(&dc, vetVertices[0], vetVertices[1], vetVertices[2]);
    DesenharTriangulo(&dc, vetVertices[2], vetVertices[3], vetVertices[0]);
}

void PainelDoDesenho::OnSize(wxSizeEvent& event) {
    wxSize tamanho = GetClientSize();
    mEscala.CarregarEscala(tamanho.x/2.0, -tamanho.y, 1.0);
    mTranslacao.CarregarTranslacao(tamanho.x/2.0, tamanho.y, 0);
    wxLogStatus(wxT("Tamanho da área de desenho: %dx%d"), tamanho.x, tamanho.y);
}

void PainelDoDesenho::TrocarTipoDeMapeamento() {
    mMapeamentoNaoLinear = not mMapeamentoNaoLinear;
    Refresh();
}

Textura::Textura()
    : wxImage(256, 256, false) {
    // Inicializar a textura com um quadriculado vermelho/verde/azul
    unsigned char* ptData = GetData();
    int valor;
    for (int lin = 0; lin < 256; ++lin) {
        for (int col = 0; col < 256; ++col) {
            valor = (lin/8 + col/8) % 3;
            if (valor == 0) {
                *ptData++ = 255; *ptData++ = 0; *ptData++ = 0;
            }
            else if (valor == 1) {
                *ptData++ = 0; *ptData++ = 255; *ptData++ = 0;
            }
            else {
                *ptData++ = 0; *ptData++ = 0; *ptData++ = 255;
            }
        }
    }
}

// Retorna a cor da textura nas coordenadas (reais) indicadas
wxColour Textura::ColourAt(float x, float y) {
    // Colocado teste para reclamar uma unica vez de coordenadas invalidas para textura, auxiliando
    // na depuracao.
    static bool aindaNaoReclamou = true;
    if (x > 1) {
        if (aindaNaoReclamou) {
            cerr << "Erro: Coordenadas (" << x << ", " << y << ") invalidas para a textura.\n";
            aindaNaoReclamou = false;
        }
        x = 1;
    }
    else if (x < 0) {
        if (aindaNaoReclamou) {
            cerr << "Erro: Coordenadas (" << x << ", " << y << ") invalidas para a textura.\n";
            aindaNaoReclamou = false;
        }
        x = 0;
    }
    if (y > 1) {
        if (aindaNaoReclamou) {
            cerr << "Erro: Coordenadas (" << x << ", " << y << ") invalidas para a textura.\n";
            aindaNaoReclamou = false;
        }
        y = 1;
    }
    else if (y < 0) {
        if (aindaNaoReclamou) {
            cerr << "Erro: Coordenadas (" << x << ", " << y << ") invalidas para a textura.\n";
            aindaNaoReclamou = false;
        }
        y = 0;
    }
    int largura = GetWidth();
    int linha  = int(y * float(GetHeight()-1));
    int coluna = int(x * float(largura-1));
    unsigned char* ptDados = GetData() + ((linha * largura + coluna) * 3);
    return wxColour(*ptDados, *(ptDados+1), *(ptDados+2));
}

// ----------------------------------------------------------------------------
// Janela: janela principal do programa

// A tabela de eventos só pode ter métodos da própria classe.
wxBEGIN_EVENT_TABLE(Janela, wxFrame)
    EVT_MENU(wxID_OPEN, Janela::AoAbrirArquivo)
    EVT_MENU(ID_MAP_NAO_LINEAR, Janela::TrocarTipoDeMapeamento)
    EVT_MENU(wxID_CLOSE, Janela::OnClose)
wxEND_EVENT_TABLE()

Janela::Janela(bool stereoWindow)
       : wxFrame(nullptr, wxID_ANY, wxT("Mapeamento de Texturas")) {

    // criar um painel de fundo para colocar a area de desenho e a imagem
    mPtPainelTextura = new PainelDaTextura(this);
    // colocar a área de desenho sobre o fundo
    mPtPainelDesenho = new PainelDoDesenho(this);
    wxSizer* ptSizer = new wxBoxSizer(wxHORIZONTAL);
    ptSizer->Add(mPtPainelDesenho, 1, wxEXPAND | wxALL, 5);
    ptSizer->Add(mPtPainelTextura, 0, wxEXPAND | wxALL, 5);
    this->SetSizer(ptSizer);

    SetIcon(wxICON(ICONE));

    // Criar a barra de menus
    wxMenu *menu = new wxMenu;
    menu->Append(wxID_OPEN, "Abrir &Textura\tCtrl-T");
    menu->AppendCheckItem(ID_MAP_NAO_LINEAR, wxT("Mapeamento não &linear\tCtrl-L"),
                          wxT("Liga ou desliga o mapeamento não linear."));
    menu->AppendSeparator();
    menu->Append(wxID_CLOSE, wxT("&Encerrar\tCtrl-Q"));
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menu, wxT("&Arquivo"));

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetClientSize(800, 600);

    mPtPainelTextura->AssociarPainelDesenho(mPtPainelDesenho);
    Show();

}

void Janela::AssociarTextura(Textura* ptTextura) {
    mPtTextura = ptTextura;
    mPtPainelTextura->AssociarTextura(ptTextura);
    mPtPainelDesenho->AssociarTextura(ptTextura);
}
void Janela::AoAbrirArquivo(wxCommandEvent& event) {
    wxFileDialog dialogo(this, wxT("Abrir Imagem"), "", "",
        "Imagens|*.png;*.jpg;*.jpeg", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (dialogo.ShowModal() == wxID_CANCEL)
        return;
    if (not mPtTextura->LoadFile(dialogo.GetPath()))
        cerr << "Erro ao abrir o arquivo '" << dialogo.GetPath() << "'.\n";
    Refresh();
}

void Janela::TrocarTipoDeMapeamento(wxCommandEvent& e) {
    mPtPainelDesenho->TrocarTipoDeMapeamento();
}

void Janela::OnClose(wxCommandEvent& WXUNUSED(event)) {
    Close(true);
}
                                                                                                                                                                                 // (C) Bruno de Oliveira Schneider - Não é permitido divulgar esta implementação - Publishing this code is forbidden
