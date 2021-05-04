#ifndef SKYBOX_H
#define SKYBOX_H

#include "visualobject.h"

class Vertex;
class Skybox : public VisualObject
{
public:
   Skybox();
   ~Skybox();
   void init(GLint matrixUniform[4]);
   void draw();
};

#endif // SKYBOX_H
