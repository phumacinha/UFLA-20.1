/// \file latadelixo.cpp
/// \brief Modelo de lata lixo usando V-ART.
/// \version $Revision: 1.0 $

#include <vart/texture.h>
#include "latadelixo.h"

#include <iostream>
using namespace std;

LataDeLixo::LataDeLixo()
{
    // Instancia materiais.
    VART::Material lGreyPlastic(VART::Color(204,204,220));
    VART::Material dGreyPlastic(VART::Color(80,80,80));

    // Dof base.
    dofBase.Set(VART::Point4D::Z(), VART::Point4D::ORIGIN(), 0, 2*3.14159265359);
    dofBase.SetDescription("dofBase");
    jointBase.AddDof(&dofBase);
    jointBase.SetDescription("jointBase");

    // Define cesto do lixo.
    cesto.SetDimensions(1.5, 4);
    cesto.SetDescription("cesto");
    cesto.SetMaterial(dGreyPlastic);
    jointBase.AddChild(cesto);

    // Translacao da tampa pro topo do cesto de lixo.
    transformacaoTampa.MakeTranslation(0, 0, 3.95);
    transformacaoTampa.SetDescription("transformacaoTampa");
    cesto.AddChild(transformacaoTampa);

    // Dof tampa.
    dofTampa.Set(VART::Point4D::Y(), VART::Point4D(-1.5, 0, 0), -1.5707963267949, 0);
    dofTampa.SetDescription("dofTampa");
    jointTampa.AddDof(&dofTampa);
    jointTampa.SetDescription("jointTampa");
    transformacaoTampa.AddChild(jointTampa);

    // Define cilindro da tampa.
    tampa.SetHeight(.5);
    tampa.SetRadius(1.55);
    tampa.SetDescription("tampa");
    tampa.SetMaterial(lGreyPlastic);
    tampa.SetPartsVisibility(VART::Cylinder::ALL);
    jointTampa.AddChild(tampa);

    // Transformacoes do pedal.
    translacaoPedal.MakeTranslation(1.4, 0, .3);
    translacaoPedal.SetDescription("translacaoPedal");
    rotacaoPedal.MakeYRotation(-0.52359877559);
    rotacaoPedal.SetDescription("rotacaoPedal");

    // Combina transformacoes.
    transformacaoPedal = translacaoPedal * rotacaoPedal;
    transformacaoPedal.SetDescription("transformacaoPedal");
    cesto.AddChild(transformacaoPedal);

    // Dof pedal.
    dofPedal.Set(VART::Point4D::Y(), VART::Point4D(0, 0, 0), 0, 0.52359877559);
    dofPedal.SetDescription("dofPedal");
    jointPedal.AddDof(&dofPedal);
    jointPedal.SetDescription("jointPedal");
    transformacaoPedal.AddChild(jointPedal);

    // Define pedal.
    pedal.MakeBox(0, .5, -.4, .4, 0, .1);
    pedal.SetDescription("pedal");
    pedal.SetMaterial(lGreyPlastic);
    jointPedal.AddChild(pedal);
}

LataDeLixo* LataDeLixo::Copy()
{
    LataDeLixo* resultPtr = new LataDeLixo;
    resultPtr->dofBase = dofBase;
    resultPtr->dofTampa = dofTampa;
    resultPtr->dofPedal = dofPedal;
    return resultPtr;
}

void LataDeLixo::Abrir(float variance)
{
    dofTampa.Move(-variance);
    dofPedal.Move(variance);
}

void LataDeLixo::Girar(float variance)
{
    // Metodo para girar a lata de lixo inteira infinitamente.
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
    bBox.SetBoundingBox(-1.5, -1.5, 0, 1.5, 1.5, 4.45);
}
