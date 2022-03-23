#ifndef HOUSE_H
#define HOUSE_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex.h"
#include "visualobject.h"

class House : public VisualObject
{
public:
    House();
    ~House();
    void init(GLint matrixUniform[4]) override;
    void draw() override;
};

#endif // HOUSE_H
