// main.cpp - vigilance camera application (biaxial joint example)

// V-ART example: Vigilance Camera

// This application shows/controls a vigilance camera that has two degrees of freedom.
// It is intended to be an example of how to use a biaxial joint.

// When running the application use 'q' to quit. Use 'i', 'j', 'k', 'l' to move
// the vigilance camera's degrees of freedom.

// Note: ViewerGlutOGL is part of "V-ART contrib".

// Changelog
// Oct 19, 2012 - Bruno de Oliveira Schneider
// - Adapted to new keyboard handler methods.
// May 30, 2006 - Bruno de Oliveira Schneider
// - Changed to work with V-ART (formerly known as VPAT).
// Mar 17, 2006 - Bruno de Oliveira Schneider
// - This example may use visual joints now.
// Jun 07, 2005 - Bruno de Oliveira Schneider
// - Code updated to comply with the new VPViewerGlutOGL version.
// Oct 01, 2004 - Bruno de Oliveira Schneider
// - Application created.

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
        virtual void OnKeyUp(int key) {
            switch (key)
            {
                case 'p':
                    ptrLata->Abrir(-0.1);
                    viewerPtr->PostRedisplay();
                    //actionPtr->Activate();
                    break;
            }
        }
        //VART::BaseAction* actionPtr;
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
    Camera camera(Point4D(8,5,6,1),Point4D(0,0,3.5,1),Point4D(0,0,1,0));
    LataDeLixo lata; // create a vigilance camera (scene object)
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
    cout << "Use 'i', 'j', 'k', 'l' to move the vigilance camera's degrees of freedom.\n";
    ViewerGlutOGL::MainLoop(); // Enter main loop (event loop)
    return 0;
}
