#ifndef DOOR_H
#define DOOR_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex.h"
#include "octahedronball.h"
#include "visualobject.h"

/**
    \brief Door class
    \author Lars Joar Bjørkeland
    \date 11/02/2021
 */

class Door : public VisualObject
{
public:
    Door();
    ~Door() override;
    void init(GLint matrixUniform[4]) override;
    void draw() override;
    void openDoor(float dt);
    void closeDoor(float dt);
    bool openingDoor{false};
    bool closingDoor{false};
private:
    float currentRotation{0};
};

#endif // DOOR_H
