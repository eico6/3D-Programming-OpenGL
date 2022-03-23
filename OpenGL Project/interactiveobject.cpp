#include "interactiveobject.h"
#include <stdlib.h>
#include <math.h>

InteractiveObject::InteractiveObject() : VisualObject() {}

InteractiveObject::~InteractiveObject() {}

void InteractiveObject::init(GLint matrixUniform[4]) {}

void InteractiveObject::draw() {}

void InteractiveObject::move(float dx, float dy, float dz)
{
    // Translate by d... * 1/("objects_scaling")
    // Cube example: scaled uniformly by 0.2f
    // Will then be: dx * 1/0.2f = dx * 5.0f
    mPosition.setColumn(3, mPosition.column(3) + QVector4D(dx, dy, dz, 0.0f));
    mMatrix.translate(dx*5.0f, dy*5.0f, dz*5.0f);

    // Converts objetc's collision box from local- to world space
    if (mLocalCollisionBox.collisionBoxIsActive())
        convertCollision();
}
