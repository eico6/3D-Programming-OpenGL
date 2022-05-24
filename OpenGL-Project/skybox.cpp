#include <iostream>
#include <sstream>
#include <math.h>
#include <QVector2D>

#include "skybox.h"

Skybox::Skybox() : VisualObject()
{
    QVector3D v0{ 0.0f,  0.0f,  1.0f}; // v0 back
    QVector3D v1{-1.0f,  0.0f,  0.0f}; // v1 left
    QVector3D v2{ 0.0f,  0.0f, -1.0f}; // v2 front
    QVector3D v3{ 1.0f,  0.0f,  0.0f}; // v3 right
    QVector3D v4{ 0.0f,  1.0f,  0.0f}; // v4 top
    QVector3D v5{ 0.0f, -1.0f,  0.0f}; // v5 bot

    // Left-back-upper side
    mVertices.push_back(Vertex(v0, v0, QVector2D(0.00f, 0.50f)));
    mVertices.push_back(Vertex(v1, v1, QVector2D(0.25f, 0.50f)));
    mVertices.push_back(Vertex(v4, v4, QVector2D(0.25f, 1.00f)));

    // Left-front-upper side
    mVertices.push_back(Vertex(v1, v1, QVector2D(0.25f, 0.50f)));
    mVertices.push_back(Vertex(v2, v2, QVector2D(0.50f, 0.50f)));
    mVertices.push_back(Vertex(v4, v4, QVector2D(0.50f, 1.00f)));

    // Right-front-upper side
    mVertices.push_back(Vertex(v2, v2, QVector2D(0.50f, 0.50f)));
    mVertices.push_back(Vertex(v3, v3, QVector2D(0.75f, 0.50f)));
    mVertices.push_back(Vertex(v4, v4, QVector2D(0.75f, 1.00f)));

    // Right-back-upper side
    mVertices.push_back(Vertex(v3, v3, QVector2D(0.75f, 0.50f)));
    mVertices.push_back(Vertex(v0, v0, QVector2D(1.00f, 0.50f)));
    mVertices.push_back(Vertex(v4, v4, QVector2D(1.00f, 1.06f)));

    // Left-back-lower side
    mVertices.push_back(Vertex(v0, v0, QVector2D(0.00f, 0.50f)));
    mVertices.push_back(Vertex(v5, v5, QVector2D(0.25f, 0.00f)));
    mVertices.push_back(Vertex(v1, v1, QVector2D(0.25f, 0.50f)));

    // Left-front-lower side
    mVertices.push_back(Vertex(v1, v1, QVector2D(0.25f, 0.50f)));
    mVertices.push_back(Vertex(v5, v5, QVector2D(0.50f, 0.00f)));
    mVertices.push_back(Vertex(v2, v2, QVector2D(0.50f, 0.50f)));

    // Right-front-lower side
    mVertices.push_back(Vertex(v2, v2, QVector2D(0.50f, 0.50f)));
    mVertices.push_back(Vertex(v5, v5, QVector2D(0.75f, 0.00f)));
    mVertices.push_back(Vertex(v3, v3, QVector2D(0.75f, 0.50f)));

    // Right-back-lower side
    mVertices.push_back(Vertex(v3, v3, QVector2D(0.75f, 0.50f)));
    mVertices.push_back(Vertex(v5, v5, QVector2D(1.00f, 0.00f)));
    mVertices.push_back(Vertex(v0, v0, QVector2D(1.00f, 0.50f)));
}

Skybox::~Skybox() {}

void Skybox::init(GLint matrixUniform[4])
{
   initializeOpenGLFunctions();

   mMaterial->setActiveShader(ShaderType::TEXTURE_SHADER);
   mMaterial->setActiveTextureSlot(3);
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

void Skybox::draw()
{
    if (renderObject){
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}
