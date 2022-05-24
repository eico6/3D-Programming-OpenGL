#ifndef GRID_H
#define GRID_H

#include <QOpenGLFunctions_4_1_Core>
#include <vector>
#include "vertex.h"
#include "visualobject.h"

class Grid : public VisualObject
{
public:
   Grid();
   ~Grid() override;
   void init(GLint matrixUniform[4]) override;
   void draw() override;
};

#endif // GRID_H
