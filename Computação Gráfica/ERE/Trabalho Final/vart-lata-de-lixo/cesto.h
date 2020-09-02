/// \file cylinder.h
/// \brief Header file for V-ART class "Cesto".
/// \version $Revision: 1.3 $

#ifndef VART_CESTO_H
#define VART_CESTO_H

#include "vart/graphicobj.h"
#include "vart/material.h"
#include "vart/cylinder.h"

namespace VART {
/// \class Cesto cylinder.h
/// \brief A cylinder or cone.
///
/// Cylinders are created along the z axis, with bottom at zero and top at height.
/// Cones are considered a special case of cylinder, where the top or bottom has zero radius.
// It is up to the Draw methods to make the above statement true.
    class Cesto : public Cylinder {
        public:

            /// \brief Creates an uninitialized cylinder.
            Cesto();

            void SetDimensions(float r, float h);
            
        private:
        // PRIVATE METHODS
            /// \brief Draws the cylinder using OpenGL engine.
            /// \return false if V-ART has not been compiled with OpenGL support.
            bool DrawInstanceOGL() const;
            float height;
            float radius;
    }; // end class declaration
} // end namespace


#endif
