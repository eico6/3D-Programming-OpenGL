#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include "visualobject.h"

class Tetrahedron : public VisualObject
{
public:
    Tetrahedron();
    ~Tetrahedron() override;
    void init(GLint matrixUniform[4]) override;
    void draw() override;
    void Overlap();
    void undoOverlap();
    bool colliding{false};

    inline bool getPickedUp() { return pickedUp; }
private:
    const float teleportDistance;
    bool pickedUp{false};
};

#endif // TETRAHEDRON_H
