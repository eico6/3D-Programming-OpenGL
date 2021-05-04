#include <iostream>
#include <sstream>
#include <math.h>
#include <QVector2D>

#include "billboard.h"

Billboard::Billboard() : VisualObject()
{
    QVector3D v0{-1.0f,  0.000f, 0.0f};   // v0 Left
    QVector3D v1{ 1.0f,  0.000f, 0.0f};   // v1 Right
    QVector3D v2{ 0.0f,  0.924f, 0.0f};   // v2 Top

    const float uniformScalar{2.0f};
    v0 *= uniformScalar;
    v1 *= uniformScalar;
    v2 *= uniformScalar;

    mVertices.push_back(Vertex(v0, v0, QVector2D(0.000f, 0.00f))); // Left
    mVertices.push_back(Vertex(v2, v2, QVector2D(0.451f, 1.00f))); // Top
    mVertices.push_back(Vertex(v1, v1, QVector2D(1.000f, 0.00f))); // Right

    mLocalCollisionBox = CollisionBox(QVector2D(v0.x() + 0.31f, v0.z()), QVector2D(v1.x() - 0.08f, v1.z() - 0.06f));
}

Billboard::~Billboard() {}

void Billboard::init(GLint matrixUniform[4])
{
   initializeOpenGLFunctions();

   mMaterial->setActiveShader(ShaderType::BILLBOARD_SHADER);
   mMaterial->setActiveTextureSlot(4);
   mMaterial->setupModelMatrixUniform(mMatrixUniform, matrixUniform);

   //Vertex Array Object - VAO
   glGenVertexArrays( 1, &mVAO );
   glBindVertexArray( mVAO );

   //Vertex Buffer Object to hold vertices - VBO
   glGenBuffers( 1, &mVBO );
   glBindBuffer( GL_ARRAY_BUFFER, mVBO );
   glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW );

   // 1rst attribute buffer : coordinates
   glBindBuffer(GL_ARRAY_BUFFER, mVBO);
   glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,sizeof(Vertex), (GLvoid*)0);
   glEnableVertexAttribArray(0);

   // 2nd attribute buffer : colors/normals
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex),  (GLvoid*)(3 * sizeof(GLfloat)) );
   glEnableVertexAttribArray(1);

   // 3rd attribute buffer : uvs
   glVertexAttribPointer(2, 2,  GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)( 6 * sizeof(GLfloat)) );
   glEnableVertexAttribArray(2);

   glBindVertexArray(0);
}

void Billboard::draw()
{
    if (renderObject){
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}
