#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex.h"
#include "interactiveobject.h"

class Cube : public InteractiveObject
{
public:
    Cube();
    ~Cube();
    void init(GLint matrixUniform[4]) override;
    void draw() override;
    void move(float dx, float dy, float dz) override;
    void moveInHouse(float dx, float dz);
    inline QVector3D getCameraTarget() const { return cameraTarget; }
private:
    QVector3D cameraOffset;
    QVector3D cameraTarget;
};

#endif // CUBE_H
