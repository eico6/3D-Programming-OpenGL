#include <iostream>
#include <sstream>
#include "octahedronball.h"
#include <math.h>

OctahedronBall::OctahedronBall(int n) : mRecursions(n), VisualObject()
{
   mVertices.reserve(3 * 8 * pow(4, mRecursions));
   oktaederUnitBall();
}

OctahedronBall::~OctahedronBall() {}

void OctahedronBall::makeTriangle(const QVector3D& v1, const QVector3D& v2, const QVector3D& v3)
{
    // Find normal vector
    QVector3D vec1(v1 - v3);
    QVector3D vec2(v1 - v2);
    QVector3D n = -QVector3D::crossProduct(vec1, vec2);
    n.normalize();

    Vertex vert(v1[0], v1[1], v1[2], n.x(), n.y(), n.z());
    mVertices.push_back(vert);
    vert = Vertex(v2[0], v2[1], v2[2], n.x(), n.y(), n.z());
    mVertices.push_back(vert);
    vert = Vertex(v3[0], v3[1], v3[2], n.x(), n.y(), n.z());
    mVertices.push_back(vert);

    // For a more smoother looking ball, the normal vector can be calculated by normalizing the sum of all adjacent normal vectors.
    // The octahedronball will always have 4 adjacent triangles per vertex
    // The only "problem" is to access these adjacent triangles as this object is procedurally generated.
}

void OctahedronBall::subDivide(const QVector3D& a, const QVector3D& b, const QVector3D& c, int n)
{
   if (n>0) {
       QVector3D v1 = a+b; v1.normalize();
       QVector3D v2 = a+c; v2.normalize();
       QVector3D v3 = c+b; v3.normalize();
       subDivide(a, v1, v2, n-1);
       subDivide(c, v2, v3, n-1);
       subDivide(b, v3, v1, n-1);
       subDivide(v3, v2, v1, n-1);
   } else {
       makeTriangle(a, b, c);
   }
}

void OctahedronBall::move(float dx, float dy, float dz)
{
    VisualObject::move(dx, dy, dz);
}

void OctahedronBall::rotateAroundYAxis(float dx)
{
    mMatrix.rotate(((180 * 0.05) / M_PI) * dx, 0.0f, -1.0f, 0.0f);

}

void OctahedronBall::oktaederUnitBall()
{
   QVector3D v0{0, 0, 1};
   QVector3D v1{1, 0, 0};
   QVector3D v2{0, 1, 0};
   QVector3D v3{-1, 0, 0};
   QVector3D v4{0, -1, 0};
   QVector3D v5{0, 0, -1};

   subDivide(v0, v1, v2, mRecursions);
   subDivide(v0, v2, v3, mRecursions);
   subDivide(v0, v3, v4, mRecursions);
   subDivide(v0, v4, v1, mRecursions);
   subDivide(v5, v2, v1, mRecursions);
   subDivide(v5, v3, v2, mRecursions);
   subDivide(v5, v4, v3, mRecursions);
   subDivide(v5, v1, v4, mRecursions);
}

void OctahedronBall::init(GLint matrixUniform[4])
{
   initializeOpenGLFunctions();

   mMaterial->setActiveShader(ShaderType::PHONG_SHADER);
   mMaterial->setActiveTextureSlot(1);
   mMaterial->setupModelMatrixUniform(mMatrixUniform, matrixUniform);

   //Vertex Array Object - VAO
   glGenVertexArrays( 1, &mVAO );
   glBindVertexArray( mVAO );

   //Vertex Buffer Object to hold vertices - VBO
   glGenBuffers( 1, &mVBO );
   glBindBuffer( GL_ARRAY_BUFFER, mVBO );

   glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW );

   glBindBuffer(GL_ARRAY_BUFFER, mVBO);
   glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,sizeof(Vertex), (GLvoid*)0);
   glEnableVertexAttribArray(0);

   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex),  (GLvoid*)(3 * sizeof(GLfloat)) );
   glEnableVertexAttribArray(1);

   glBindVertexArray(0);
}

void OctahedronBall::draw()
{
    if (renderObject){
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}
