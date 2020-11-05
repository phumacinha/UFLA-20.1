/// \file latadelixo.h
/// \brief Modelo de lata de lixo usando V-ART.
/// \version $Revision: 1.0 $

// ChangeLog is at the implementation file

#ifndef LATADELIXO_H
#define LATADELIXO_H

#include <vart/graphicobj.h>
#include <vart/cylinder.h>
#include <vart/box.h>
#include <vart/uniaxialjoint.h>
#include <bucket.h>

class LataDeLixo : public VART::GraphicObj
{
    public:
        LataDeLixo();
        void Abrir(float variance);
        void Girar(float variance);
        /// Computes the bounding box.
        virtual void ComputeBoundingBox();
        virtual LataDeLixo* Copy();
    private:
    // PRIVATE METHODS
        virtual bool DrawInstanceOGL() const;
    // PRIVATE ATTRIBUTES
        VART::Dof dofBase;
        VART::UniaxialJoint jointBase;
        
        VART::Bucket cesto;
        VART::Cylinder tampa;
        VART::Transform transformacaoTampa;
        VART::Box pedal;
        VART::Transform translacaoPedal;
        VART::Transform rotacaoPedal;
        VART::Transform transformacaoPedal;

        VART::Dof dofTampa;
        VART::UniaxialJoint jointTampa;

        VART::Dof dofPedal;
        VART::UniaxialJoint jointPedal;
};

#endif
