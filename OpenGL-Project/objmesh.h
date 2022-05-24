#ifndef OBJMESH_H
#define OBJMESH_H
#include "visualobject.h"


class ObjMesh : public VisualObject
{
public:
    ObjMesh(std::string filename);
    ~ObjMesh() override;

    virtual void draw() override;
    virtual void init(GLint matrixUniform[4]) override;

private:
    void readFile(std::string filename);
};

#endif // OBJMESH_H
