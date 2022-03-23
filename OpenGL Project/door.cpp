#include "vertex.h"
#include <math.h>
#include <sstream>
#include <octahedronball.h>
#include <stdio.h>
#include "door.h"

Door::Door() : VisualObject ()
{
    //Door
    mVertices.push_back(Vertex{ 0.0f,  0.0f,  0.0f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.5f,  0.0f,  0.0f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.5f,  1.0f,  0.0f, 0.5f,  0.2f, 0.6f});

    mVertices.push_back(Vertex{ 0.5f,  1.0f,  0.0f, 0.7f,  0.0f, 0.3f});
    mVertices.push_back(Vertex{ 0.0f,  1.0f,  0.0f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.0f,  0.0f,  0.0f, 0.5f,  0.2f, 0.6f});

    //Handle outside front
    mVertices.push_back(Vertex{ 0.45f,  0.5f,  0.02f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.3f,  0.5f,  0.02f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.3f,  0.55f,  0.02f, 0.5f,  0.2f, 0.6f});

    mVertices.push_back(Vertex{ 0.3f,  0.55f,  0.02f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.45f,  0.55f,  0.02f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.45f,  0.5f,  0.02f, 0.5f,  0.2f, 0.6f});

    //Handle outside back
    mVertices.push_back(Vertex{ 0.45f,  0.5f,  0.01f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.3f,  0.5f,  0.01f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.3f,  0.55f,  0.01f, 0.5f,  0.2f, 0.6f});

    mVertices.push_back(Vertex{ 0.3f,  0.55f,  0.01f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.45f,  0.55f,  0.01f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.45f,  0.5f,  0.01f, 0.5f,  0.2f, 0.6f});

    //Handle outside top
    mVertices.push_back(Vertex{ 0.45f,  0.55f,  0.02f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.3f,  0.55f,  0.02f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.45f,  0.55f,  0.01f, 0.5f,  0.2f, 0.6f});

    mVertices.push_back(Vertex{ 0.3f,  0.55f,  0.02f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.3f,  0.55f,  0.01f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.45f,  0.55f,  0.01f, 0.5f,  0.2f, 0.6f});

    //Handle outside bottom
    mVertices.push_back(Vertex{ 0.45f,  0.5f,  0.02f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.3f,  0.5f,  0.02f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.45f,  0.5f,  0.01f, 0.5f,  0.2f, 0.6f});

    mVertices.push_back(Vertex{ 0.3f,  0.5f,  0.02f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.3f,  0.5f,  0.01f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.45f,  0.5f,  0.01f, 0.5f,  0.2f, 0.6f});

    //Handle outside right side
    mVertices.push_back(Vertex{ 0.3f,  0.5f,  0.02f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.3f,  0.5f,  0.01f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.3f,  0.55f,  0.02f, 0.5f,  0.2f, 0.6f});

    mVertices.push_back(Vertex{ 0.3f,  0.55f,  0.02f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.3f,  0.55f,  0.01f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.3f,  0.50f,  0.01f, 0.5f,  0.2f, 0.6f});

    //Handle connector left side
    mVertices.push_back(Vertex{ 0.45f,  0.5f,  0.02f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.45f,  0.5f,  -0.02f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.45f,  0.55f,  0.02f, 0.5f,  0.2f, 0.6f});

    mVertices.push_back(Vertex{ 0.45f,  0.55f,  0.02f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.45f,  0.55f,  -0.02f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.45f,  0.50f,  -0.02f, 0.5f,  0.2f, 0.6f});

    //Handle inside front
    mVertices.push_back(Vertex{ 0.45f,  0.5f,  -0.02f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.3f,  0.5f,  -0.02f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.3f,  0.55f,  -0.02f, 0.5f,  0.2f, 0.6f});

    mVertices.push_back(Vertex{ 0.3f,  0.55f,  -0.02f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.45f,  0.55f,  -0.02f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.45f,  0.5f,  -0.02f, 0.5f,  0.2f, 0.6f});

    //Handle inside back
    mVertices.push_back(Vertex{ 0.45f,  0.5f,  -0.01f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.3f,  0.5f,  -0.01f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.3f,  0.55f,  -0.01f, 0.5f,  0.2f, 0.6f});

    mVertices.push_back(Vertex{ 0.3f,  0.55f,  -0.01f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.45f,  0.55f,  -0.01f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.45f,  0.5f,  -0.01f, 0.5f,  0.2f, 0.6f});

    //Handle inside right side
    mVertices.push_back(Vertex{ 0.3f,  0.5f,  -0.02f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.3f,  0.5f,  -0.01f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.3f,  0.55f,  -0.02f, 0.5f,  0.2f, 0.6f});

    mVertices.push_back(Vertex{ 0.3f,  0.55f,  -0.02f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.3f,  0.55f,  -0.01f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.3f,  0.50f,  -0.01f, 0.5f,  0.2f, 0.6f});

    //Handle inside top
    mVertices.push_back(Vertex{ 0.45f,  0.55f,  -0.02f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.3f,  0.55f,  -0.02f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.45f,  0.55f,  -0.01f, 0.5f,  0.2f, 0.6f});

    mVertices.push_back(Vertex{ 0.3f,  0.55f,  -0.02f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.3f,  0.55f,  -0.01f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.45f,  0.55f,  -0.01f, 0.5f,  0.2f, 0.6f});

    //Handle inside bottom
    mVertices.push_back(Vertex{ 0.45f,  0.5f,  -0.02f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.3f,  0.5f,  -0.02f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.45f,  0.5f,  -0.01f, 0.5f,  0.2f, 0.6f});

    mVertices.push_back(Vertex{ 0.3f,  0.5f,  -0.02f, 0.3f,  0.0f, 0.5f});
    mVertices.push_back(Vertex{ 0.3f,  0.5f,  -0.01f, 0.5f,  0.2f, 0.6f});
    mVertices.push_back(Vertex{ 0.45f,  0.5f,  -0.01f, 0.5f,  0.2f, 0.6f});

    mMatrix.setToIdentity();
}

Door::~Door() {}

void Door::init(GLint matrixUniform[4])
{
    initializeOpenGLFunctions();

    mMaterial->setActiveShader(ShaderType::PLAIN_SHADER);
    mMaterial->setupModelMatrixUniform(mMatrixUniform, matrixUniform);

    glGenVertexArrays( 1, &mVAO );
    glBindVertexArray( mVAO );

    glGenBuffers( 1, &mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );

    glBufferData( GL_ARRAY_BUFFER,                     //what buffer type
                  mVertices.size() * sizeof( Vertex ), //how big buffer do we need
                  mVertices.data(),                    //the actual vertices
                  GL_STATIC_DRAW                       //should the buffer be updated on the GPU
                  );

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(
                0,                                     // attribute. No particular reason for 0, but must match layout(location = 0) in the vertex shader.
                3,                                     // size
                GL_FLOAT,                              // data type
                GL_FALSE,                              // normalized?
                sizeof(Vertex),                        // stride
                reinterpret_cast<GLvoid*>(0));         // array buffer offset
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex),  reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

void Door::draw()
{
    if (renderObject){
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}

void Door::openDoor(float dt)
{
    if(openingDoor == true)
    {
        if(currentRotation < 90) {
            float degrees = (180 * dt) / M_PI;
            currentRotation += degrees;
            mMatrix.rotate(degrees, 0, -1, 0);
        } else {
            openingDoor = false;
        }
    }
}

void Door::closeDoor(float dt)
{
    if(closingDoor == true)
    {
        if(currentRotation >= 1.0f) {
            float degrees = (180 * dt) / M_PI;
            currentRotation += degrees;
            mMatrix.rotate(degrees, 0, -1, 0);
        } else {
            closingDoor = false;
        }
    }
}
