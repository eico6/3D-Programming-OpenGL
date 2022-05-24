#ifndef OCTAHEDRONBALL_H
#define OCTAHEDRONBALL_H

#include "visualobject.h"

class Vertex;
class OctahedronBall : public VisualObject {
private:
   int mRecursions;
   void makeTriangle(const QVector3D& v1, const QVector3D& v2, const QVector3D& v3);
   void subDivide(const QVector3D& a, const QVector3D& b, const QVector3D& c, int n);
   void move(float dx, float dy, float dz) override;
   void oktaederUnitBall();
public:
   OctahedronBall(int n=0);
   ~OctahedronBall();
   void init(GLint matrixUniform[4]);
   void draw();
   void rotateAroundYAxis(float dx);
};


#endif // OCTAHEDRONBALL_H
