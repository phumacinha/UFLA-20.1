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
    VART::Material dGreyPlastic(VART::Color(127,127,127));

    VART::Texture quadriculado("textura-chao.jpg");
    VART::Material materialQuadriculado(quadriculado);

    base.MakeBox(-20,20,-20,20,-.001,0);
    base.SetMaterial(materialQuadriculado);
    base.SetBBoxVisibility(VART::Box::NONE);

    dofBase.Set(VART::Point4D::Z(), VART::Point4D::ORIGIN(), -3.14159265359, 3.14159265359);
    dofBase.SetDescription("dofBase");
    jointBase.AddDof(&dofBase);
    jointBase.SetDescription("jointBase");
    jointBase.AddChild(base);

    cesto.SetHeight(4);
    cesto.SetRadius(1.5);
    cesto.SetDescription("cesto");
    cesto.SetMaterial(dGreyPlastic);
    cesto.SetPartsVisibility(VART::Cylinder::ALL);
    jointBase.AddChild(cesto);

    tampaTrans.MakeTranslation(0, 0, 3.95);
    tampaTrans.SetDescription("tampaTrans");
    cesto.AddChild(tampaTrans);

    dofTampa.Set(VART::Point4D::Y(), VART::Point4D(-1.5, 0, 0), -1.5707963267949, 0);
    dofTampa.SetDescription("dofTampa");
    jointTampa.AddDof(&dofTampa);
    jointTampa.SetDescription("jointTampa");
    tampaTrans.AddChild(jointTampa);

    tampa.SetHeight(.5);
    tampa.SetRadius(1.55);
    tampa.SetDescription("tampa");
    tampa.SetMaterial(lGreyPlastic);
    tampa.SetPartsVisibility(VART::Cylinder::ALL);
    jointTampa.AddChild(tampa);

    pedalTrans.MakeTranslation(1.4, 0, .3);
    pedalTrans.SetDescription("pedalTrans");
    cesto.AddChild(pedalTrans);

    pedalRot.MakeYRotation(-0.52359877559);
    pedalRot.SetDescription("pedalRot");
    pedalTrans.AddChild(pedalRot);

    dofPedal.Set(VART::Point4D::Y(), VART::Point4D(0, 0, 0), 0, 0.52359877559);
    dofPedal.SetDescription("dofPedal");
    jointPedal.AddDof(&dofPedal);
    jointPedal.SetDescription("jointPedal");
    pedalRot.AddChild(jointPedal);

    pedal.MakeBox(0, .5, -.4, .4, 0, .1);
    pedal.SetDescription("pedal");
    pedal.SetMaterial(lGreyPlastic);
    jointPedal.AddChild(pedal);
    
    //dofPedal.MoveTo(-0.52359877559);
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
    dofBase.Move(-variance);
}

/*
void LataDeLixo::Flex(float variance)
{
    flexion.Move(variance);
}
void LataDeLixo::Adduct(float variance)
{
    aduction.Move(variance);
}
*/
bool LataDeLixo::DrawInstanceOGL() const
{
    jointBase.DrawOGL();
    return true;
}

void LataDeLixo::ComputeBoundingBox() {
    //FixMe: Computing the bbox according to the current joint state would be better.
    bBox.SetBoundingBox(-1.5, -1.5, 0, 1.5, 1.5, 3.1);
}
