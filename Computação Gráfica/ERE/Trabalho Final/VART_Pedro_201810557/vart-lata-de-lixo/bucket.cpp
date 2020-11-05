/// \file bucket.cpp
/// \brief Implementation file for V-ART class "Bucket".
/// \version $Revision: 1.0 $

#include "bucket.h"
#ifdef WIN32
#include <windows.h>
#endif
#ifdef VART_OGL
#include <GL/glu.h>
#endif

//?
#include <iostream>
using namespace std;


VART::Bucket::Bucket() : VART::Cylinder()
{
}

void VART::Bucket::SetDimensions(float r, float h)
{
    radius = r;
    height = h;
    SetRadius(r);
    SetHeight(h);
}

bool VART::Bucket::DrawInstanceOGL() const
{
#ifdef VART_OGL
    GLUquadricObj* qObj = gluNewQuadric();
    bool result = true;
    
    glDisable(GL_CULL_FACE);

    if (show)
    {
        switch (howToShow)
        {
            case LINES:
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                break;
            case POINTS:
                glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
                break;
            default:
                glPolygonMode(GL_FRONT, GL_FILL);
                break;
        }
        if ( GetMaterial().GetTexture().HasData() ) {
            gluQuadricTexture(qObj,GL_TRUE);
        }
        result = GetMaterial().DrawOGL();
        // Render sides
        gluQuadricDrawStyle(qObj, GLU_FILL);
        gluQuadricNormals(qObj, GLU_SMOOTH);
        gluCylinder(qObj, radius, radius, height, 15, 1);

        // Render bottom
        gluQuadricOrientation(qObj,GLU_INSIDE);
        gluDisk(qObj, 0.0, radius, 15, 1);
        
        gluDeleteQuadric(qObj);
    }
    if (bBox.visible) // Is the bounding box visible?
        bBox.DrawInstanceOGL();
    if (recBBox.visible)
        recBBox.DrawInstanceOGL();
    return result;
#else
    return false;
#endif
}
