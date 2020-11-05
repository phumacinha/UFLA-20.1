#include <vart/scene.h>
#include <vart/cylinder.h>
#include <vart/light.h>
#include <vart/point4d.h>
#include <vart/contrib/viewerglutogl.h>
#include "latadelixo.h"

#include <iostream>

using namespace std;
using namespace VART;

// Define the keyboard handler
class KeyboardHandler : public ViewerGlutOGL::KbHandler
{
    public:
        KeyboardHandler(LataDeLixo* lata) {
            ptrLata = lata;
        }
        virtual void OnKeyDown(int key) {
            switch (key)
            {
                case 'i':
                    ptrLata->Abrir(0.05);
                    viewerPtr->PostRedisplay();
                    break;
                case 'k':
                    ptrLata->Abrir(-0.03);
                    viewerPtr->PostRedisplay();
                    break;
                case 'j':
                    ptrLata->Girar(0.01);
                    viewerPtr->PostRedisplay();
                    break;
                case 'l':
                    ptrLata->Girar(-0.01);
                    viewerPtr->PostRedisplay();
                    break;

            }
        }
        
    private:
        LataDeLixo* ptrLata;
};

// The application itself:
int main(int argc, char* argv[])
{
    ViewerGlutOGL::Init(&argc, argv); // Initialize GLUT

    static Scene scene; // create a scene
    static ViewerGlutOGL viewer; // create a viewer (application window)
    // create a camera (scene observer)
    Camera camera(Point4D(8,0,7,1),Point4D(0,0,3.5,1),Point4D(-0.40081883401970775,0,0.9161573349021892,0));
    LataDeLixo lata; // cria uma lata de lixo (objeto de cena)
    Light luz("luz", .6f, .6f, VART::Color::WHITE(), VART::Point4D(0,0,5,0));

    Texture quadriculado("textura-chao.jpg");
    Material materialQuadriculado(quadriculado);
    Box chao;

    chao.MakeBox(-20,20,-20,20,-.002,-.001);
    chao.SetMaterialBoxFace(materialQuadriculado, Box::TOP_FACE);
    chao.AddChild(lata);

    // Build up the scene
    scene.SetBackgroundColor(VART::Color::WHITE());
    scene.AddObject(&chao);
    scene.AddLight(&luz);
    scene.AddCamera(&camera);

    #ifdef VISUAL_JOINTS
    Dof::axisSize = 2.3f;
    #endif

    // Set up the viewer
    viewer.SetScene(scene); // attach the scene
    KeyboardHandler kbh(&lata); // create a keyboard handler
    viewer.SetKbHandler(&kbh); // attach the keyboard handler

    // Run application
    scene.DrawLightsOGL(); // Set OpenGL's lights' state
    cout << "COMANDOS:" << endl;
    cout << "Use 'i' para abrir a tampa da lixeira." << endl;
    cout << "Use 'k' para fechar a tampa da lixeira." << endl;
    cout << "Use 'j' para girar a lixeira no sentido horário." << endl;
    cout << "Use 'l' para girar a lixeira no sentido antihorário." << endl;
    ViewerGlutOGL::MainLoop(); // Enter main loop (event loop)
    return 0;
}
