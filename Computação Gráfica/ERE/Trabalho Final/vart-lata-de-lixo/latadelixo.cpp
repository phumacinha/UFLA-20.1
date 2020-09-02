/// \file vigilancecamera.cpp
/// \brief Example class for VPAT (implementation)
/// \version $Revision: 1.1 $

// ChangeLog
// Jul 07, 2008 - Bruno de Oliveira Schneider
// - Added LataDeLixo::Copy() because it was added at SceneNode.
// Jun 01, 2006 - Bruno de Oliveira Schneider
// - General renaming to account for project rename (VPAT->V-ART).
// Mar 17, 2006 - Bruno de Oliveira Schneider
// - Uses new method VPCylinder::SetPartsVisibility.
// Mar 21, 2005 - Bruno de Oliveira Schneider
// - Added ComputeBoundingBox.
#include <vart/texture.h>
#include "latadelixo.h"

#include <iostream>
using namespace std;

LataDeLixo::LataDeLixo()
{
    VART::Material lGreyPlastic(VART::Color(204,204,220));
    VART::Material dGreyPlastic(VART::Color(80,80,80));

    dofBase.Set(VART::Point4D::Z(), VART::Point4D::ORIGIN(), 0, 2*3.14159265359);
    dofBase.SetDescription("dofBase");
    jointBase.AddDof(&dofBase);
    jointBase.SetDescription("jointBase");

    cesto.SetDimensions(1.5, 4);
    cesto.SetDescription("cesto");
    cesto.SetMaterial(dGreyPlastic);
    jointBase.AddChild(cesto);

    transformacaoTampa.MakeTranslation(0, 0, 3.95);
    transformacaoTampa.SetDescription("transformacaoTampa");
    cesto.AddChild(transformacaoTampa);

    dofTampa.Set(VART::Point4D::Y(), VART::Point4D(-1.5, 0, 0), -1.5707963267949, 0);
    dofTampa.SetDescription("dofTampa");
    jointTampa.AddDof(&dofTampa);
    jointTampa.SetDescription("jointTampa");
    transformacaoTampa.AddChild(jointTampa);

    tampa.SetHeight(.5);
    tampa.SetRadius(1.55);
    tampa.SetDescription("tampa");
    tampa.SetMaterial(lGreyPlastic);
    tampa.SetPartsVisibility(VART::Cylinder::ALL);
    jointTampa.AddChild(tampa);

    translacaoPedal.MakeTranslation(1.4, 0, .3);
    translacaoPedal.SetDescription("translacaoPedal");
    rotacaoPedal.MakeYRotation(-0.52359877559);
    rotacaoPedal.SetDescription("rotacaoPedal");

    transformacaoPedal = translacaoPedal * rotacaoPedal;
    transformacaoPedal.SetDescription("transformacaoPedal");
    cesto.AddChild(transformacaoPedal);

    dofPedal.Set(VART::Point4D::Y(), VART::Point4D(0, 0, 0), 0, 0.52359877559);
    dofPedal.SetDescription("dofPedal");
    jointPedal.AddDof(&dofPedal);
    jointPedal.SetDescription("jointPedal");
    transformacaoPedal.AddChild(jointPedal);

    pedal.MakeBox(0, .5, -.4, .4, 0, .1);
    pedal.SetDescription("pedal");
    pedal.SetMaterial(lGreyPlastic);
    jointPedal.AddChild(pedal);
}

LataDeLixo* LataDeLixo::Copy()
{
    LataDeLixo* resultPtr = new LataDeLixo;
    //resultPtr->flexion = flexion;
    //resultPtr->aduction = aduction;
    return resultPtr;
}

void LataDeLixo::Abrir(float variance)
{
    dofTampa.Move(-variance);
    dofPedal.Move(variance);
}

void LataDeLixo::Girar(float variance)
{
    float newCurrent = dofBase.GetCurrent() - variance;
    if (newCurrent > 1) {
        dofBase.MoveTo(0);
    }
    else if (newCurrent < 0) {
        dofBase.MoveTo(1);
    }
    
    dofBase.Move(-variance);
}

bool LataDeLixo::DrawInstanceOGL() const
{
    jointBase.DrawOGL();
    return true;
}

void LataDeLixo::ComputeBoundingBox() {
    //FixMe: Computing the bbox according to the current joint state would be better.
    bBox.SetBoundingBox(-1.5, -1.5, 0, 1.5, 1.5, 3.1);
}
