#ifndef BILLBOARD_H
#define BILLBOARD_H


#include "visualobject.h"

class Vertex;
class Billboard : public VisualObject
{
public:
   Billboard();
   ~Billboard();
   void init(GLint matrixUniform[4]);
   void draw();
};

#endif // BILLBOARD_H
