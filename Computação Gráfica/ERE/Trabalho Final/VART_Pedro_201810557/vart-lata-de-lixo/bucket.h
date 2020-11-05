/// \file bucket.h
/// \brief Header file for V-ART class "Bucket".
/// \version $Revision: 1.0 $

#ifndef VART_BUCKET_H
#define VART_BUCKET_H

#include "vart/graphicobj.h"
#include "vart/material.h"
#include "vart/cylinder.h"

namespace VART {
/// \class Bucket bucket.h
/// \brief A cylinder without top face.
///
/// Buckets are created along the z axis, with bottom at zero and top at height.
/// There is not top face and culling face is disabled.
    class Bucket : public Cylinder {
        public:

            /// \brief Creates an uninitialized bucket.
            Bucket();

            void SetDimensions(float r, float h);
            
        private:
        // PRIVATE METHODS
            /// \brief Draws the bucket using OpenGL engine.
            /// \return false if V-ART has not been compiled with OpenGL support.
            bool DrawInstanceOGL() const;
            float height;
            float radius;
    }; // end class declaration
} // end namespace


#endif
