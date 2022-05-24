#include "tetrahedron.h"

Tetrahedron::Tetrahedron()
    : teleportDistance{100.0f}
{
    mVertices.push_back(Vertex{0.f, 0.f, 1.f, 0.1f,  0.5f, 0.1f});       //F
    mVertices.push_back(Vertex{-0.865f, 0.f, -0.5f, 0.1f,  0.2f, 0.8f}); //D
    mVertices.push_back(Vertex{0.865f, 0.f, -0.5f, 1.0f,  0.7f, 0.2f});  //E

    mVertices.push_back(Vertex{0.f, 0.f, 1.f, 0.1f,  0.5f, 0.1f});       //F
    mVertices.push_back(Vertex{0.865f, 0.f, -0.5f, 1.0f,  0.7f, 0.2f});  //E
    mVertices.push_back(Vertex{0.f, 1.85f, 0.f, 0.8f, 0.8f, 0.8f});      //Origo

    mVertices.push_back(Vertex{-0.865f, 0.f, -0.5f, 0.1f,  0.2f, 0.8f}); //D
    mVertices.push_back(Vertex{0.f, 0.f, 1.f, 0.1f,  0.5f, 0.1f});       //F
    mVertices.push_back(Vertex{0.f, 1.85f, 0.f, 0.8f, 0.8f, 0.8f});      //Origo

    mVertices.push_back(Vertex{0.865f, 0.f, -0.5f, 1.0f,  0.7f, 0.2f});  //E
    mVertices.push_back(Vertex{-0.865f, 0.f, -0.5f, 0.1f,  0.2f, 0.8f}); //D
    mVertices.push_back(Vertex{0.f, 1.85f, 0.f, 0.8f, 0.8f, 0.8f});      //Origo

    mLocalCollisionBox = CollisionBox(QVector2D(-0.865f, 0.800f), QVector2D(0.865f, -0.500f));

    mMatrix.setToIdentity();
}

Tetrahedron::~Tetrahedron() {}

void Tetrahedron::init(GLint matrixUniform[4])
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

void Tetrahedron::draw()
{
    if (renderObject){
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}

void Tetrahedron::Overlap()
{
    // Teleports the trophy up into the air to simulate a pick-up effect
    if (!pickedUp){
        mMatrix.translate(0.0f, teleportDistance, 0.f);
        pickedUp = true;
    }
}

void Tetrahedron::undoOverlap()
{
    // Teleports the trophy back down to its original position
    if (pickedUp){
        mMatrix.translate(0.0f, -teleportDistance, 0.0f);
        pickedUp = false;
    }
}
