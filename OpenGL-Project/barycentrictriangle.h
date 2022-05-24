#ifndef BARYCENTRICTRIANGLE_H
#define BARYCENTRICTRIANGLE_H

#include "visualobject.h"

// ------------------------------------------------------------------
// THIS CLASS IS USED FOR DEBUGGING / TESTING OUT NEW FUNCTIONALITIES
// ------------------------------------------------------------------

class BarycentricTriangle : public VisualObject
{
public:
    BarycentricTriangle();
    void init(GLint matrixUniform[4]) override;
    void draw() override;
};

#endif // BARYCENTRICTRIANGLE_H
