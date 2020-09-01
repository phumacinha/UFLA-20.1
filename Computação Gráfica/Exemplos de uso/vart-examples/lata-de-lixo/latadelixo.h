/// \file vigilancecamera.h
/// \brief Example class for VPAT (headers)
/// \version $Revision: 1.1 $

// ChangeLog is at the implementation file

#ifndef LATADELIXO_H
#define LATADELIXO_H

#include <vart/graphicobj.h>
#include <vart/cylinder.h>
#include <vart/box.h>
#include <vart/jointaction.h>
#include <vart/uniaxialjoint.h>
#include <vart/biaxialjoint.h>

class LataDeLixo : public VART::GraphicObj
{
    public:
        LataDeLixo();
        void Abrir(float variance);
        void Girar(float variance);
        VART::JointAction* AnimacaoFechar();
        /// Computes the bounding box.
        virtual void ComputeBoundingBox();
        virtual LataDeLixo* Copy();
    private:
    // PRIVATE METHODS
        virtual bool DrawInstanceOGL() const;
    // PRIVATE ATTRIBUTES
        VART::Dof altura;
        VART::Dof azimute;
        VART::Dof dofBase;
        VART::UniaxialJoint jointBase;
        VART::Box base;

        VART::Cylinder cesto;
        VART::Cylinder tampa;
        VART::Transform tampaTrans;
        VART::Box pedal;
        VART::Transform pedalTrans;
        VART::Transform pedalRot;

        VART::Dof dofTampa;
        VART::UniaxialJoint jointTampa;

        VART::Dof dofPedal;
        VART::UniaxialJoint jointPedal;
};

#endif
