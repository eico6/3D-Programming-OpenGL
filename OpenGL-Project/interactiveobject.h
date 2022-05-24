#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H

#include "visualobject.h"

class InteractiveObject : public VisualObject
{
public:
   InteractiveObject();
   ~InteractiveObject();
   void init(GLint matrixUniform[4]) override;
   void draw() override;
   virtual void move(float dx, float dy, float dz) override;
   inline const QVector3D getPos() { return QVector3D(mPosition.column(3)); }

};

#endif // INTERACTIVEOBJECT_H
