#include "house.h"
#include "vertex.h"

House::House()
{
    //Wall 1
    mVertices.push_back(Vertex{-0.125, 0, 0.5, -0.125, 0, 0.5});
    mVertices.push_back(Vertex{-0.125, 0.5, 0.5, -0.125, 0.5, 0.5});
    mVertices.push_back(Vertex{-0.5, 0.5, 0.5, -0.5, 0.5, 0.5});

    mVertices.push_back(Vertex{-0.125, 0, 0.5, -0.125, 0, 0.5});
    mVertices.push_back(Vertex{-0.5, 0, 0.5, -0.5, 0, 0.5});
    mVertices.push_back(Vertex{-0.5, 0.5, 0.5, -0.5, 0.5, 0.5});

    //Wall 2
    mVertices.push_back(Vertex{-0.5, 0.5, 0.5, -0.5, 0.5, 0.5});
    mVertices.push_back(Vertex{-0.5, 0, 0.5, -0.5, 0, 0.5});
    mVertices.push_back(Vertex{-0.5, 0.5, -0.5, -0.5, 0.5, -0.5});

    mVertices.push_back(Vertex{-0.5, 0, -0.5, -0.5, 0, -0.5});
    mVertices.push_back(Vertex{-0.5, 0, 0.5, -0.5, 0, 0.5});
    mVertices.push_back(Vertex{-0.5, 0.5, -0.5, -0.5, 0.5, -0.5});

    //Wall 3
    mVertices.push_back(Vertex{-0.5, 0, -0.5, -0.5, 0, -0.5});
    mVertices.push_back(Vertex{0.5, 0.5, -0.5, 0.5, 0.5, -0.5});
    mVertices.push_back(Vertex{-0.5, 0.5, -0.5, -0.5, 0.5, -0.5});

    mVertices.push_back(Vertex{-0.5, 0, -0.5, -0.5, 0, -0.5});
    mVertices.push_back(Vertex{0.5, 0.5, -0.5, 0.5, 0.5, -0.5});
    mVertices.push_back(Vertex{0.5, 0, -0.5, 0.5, 0, -0.5});

    //Wall 4
    mVertices.push_back(Vertex{0.5, 0.5, 0.5, 0.5, 0.5, 0.5});
    mVertices.push_back(Vertex{0.5, 0.5, -0.5, 0.5, 0.5, -0.5});
    mVertices.push_back(Vertex{0.5, 0, -0.5, 0.5, 0, -0.5});

    mVertices.push_back(Vertex{0.5, 0.5, 0.5, 0.5, 0.5, 0.5});
    mVertices.push_back(Vertex{0.5, 0, 0.5, 0.5, 0, 0.5});
    mVertices.push_back(Vertex{0.5, 0, -0.5, 0.5, 0, -0.5});

    //Wall 5
    mVertices.push_back(Vertex{0.5, 0.5, 0.5, 0.5, 0.5, 0.5});
    mVertices.push_back(Vertex{0.5, 0, 0.5, 0.5, 0, 0.5});
    mVertices.push_back(Vertex{0.125, 0.5, 0.5, 0.125, 0.5, 0.5});

    mVertices.push_back(Vertex{0.125, 0, 0.5, 0.125, 0, 0.5});
    mVertices.push_back(Vertex{0.5, 0, 0.5, 0.5, 0, 0.5});
    mVertices.push_back(Vertex{0.125, 0.5, 0.5, 0.125, 0.5, 0.5});

    //Wall upper 1
    mVertices.push_back(Vertex{0.5, 0.5, 0.5, 0.5, 0.5, 0.5});
    mVertices.push_back(Vertex{0.5, 1, 0.5, 0.5, 1, 0.5});
    mVertices.push_back(Vertex{-0.5, 1.0, 0.5, -0.5, 1.0, 0.5});

    mVertices.push_back(Vertex{0.5, 0.5, 0.5, 0.5, 0.5, 0.5});
    mVertices.push_back(Vertex{-0.5, 0.5, 0.5, -0.5, 0.5, 0.5});
    mVertices.push_back(Vertex{-0.5, 1.0, 0.5, -0.5, 1.0, 0.5});

    //Wall upper 2
    mVertices.push_back(Vertex{-0.5, 1.0, -0.5, -0.5, 1.0, -0.5});
    mVertices.push_back(Vertex{-0.5, 0.5, 0.5, -0.5, 0.5, 0.5});
    mVertices.push_back(Vertex{-0.5, 1.0, 0.5, -0.5, 1.0, 0.5});

    mVertices.push_back(Vertex{-0.5, 1.0, -0.5, -0.5, 1.0, -0.5});
    mVertices.push_back(Vertex{-0.5, 0.5, 0.5, -0.5, 0.5, 0.5});
    mVertices.push_back(Vertex{-0.5, 0.5, -0.5, -0.5, 0.5, -0.5});

    //Wall upper 3
    mVertices.push_back(Vertex{-0.5, 1.0, -0.5, -0.5, 1.0, -0.5});
    mVertices.push_back(Vertex{0.5, 1.0, -0.5, 0.5, 1.0, -0.5});
    mVertices.push_back(Vertex{-0.5, 0.5, -0.5, -0.5, 0.5, -0.5});

    mVertices.push_back(Vertex{0.5, 0.5, -0.5, 0.5, 0.5, -0.5});
    mVertices.push_back(Vertex{0.5, 1.0, -0.5, 0.5, 1.0, -0.5});
    mVertices.push_back(Vertex{-0.5, 0.5, -0.5, -0.5, 0.5, -0.5});

    //Wall upper 4
    mVertices.push_back(Vertex{0.5, 0.5, -0.5, 0.5, 0.5, -0.5});
    mVertices.push_back(Vertex{0.5, 1.0, -0.5, 0.5, 1.0, -0.5});
    mVertices.push_back(Vertex{0.5, 1.0, 0.5, 0.5, 1.0, 0.5});

    mVertices.push_back(Vertex{0.5, 0.5, -0.5, 0.5, 0.5, -0.5});
    mVertices.push_back(Vertex{0.5, 0.5, 0.5, 0.5, 0.5, 0.5});
    mVertices.push_back(Vertex{0.5, 1.0, 0.5, 0.5, 1.0, 0.5});

    //Roof
    mVertices.push_back(Vertex{0.5, 1.0, 0.5, 0.5, 1.0, 0.5});
    mVertices.push_back(Vertex{-0.5, 1.0, 0.5, -0.5, 1.0, 0.5});
    mVertices.push_back(Vertex{-0.5, 1.0, -0.5, -0.5, 1.0, -0.5});

    mVertices.push_back(Vertex{0.5, 1.0, 0.5, 0.5, 1.0, 0.5});
    mVertices.push_back(Vertex{0.5, 1.0, -0.5, 0.5, 1.0, -0.5});
    mVertices.push_back(Vertex{-0.5, 1.0, -0.5, -0.5, 1.0, -0.5});

    //Floor
    mVertices.push_back(Vertex{0.5, 0.0, 0.5, 0.5, 0.0, 0.5});
    mVertices.push_back(Vertex{-0.5, 0.0, 0.5, -0.5, 0.0, 0.5});
    mVertices.push_back(Vertex{-0.5, 0.0, -0.5, -0.5, 0.0, -0.5});

    mVertices.push_back(Vertex{0.5, 0.0, 0.5, 0.5, 0.0, 0.5});
    mVertices.push_back(Vertex{0.5, 0.0, -0.5, 0.5, 0.0, -0.5});
    mVertices.push_back(Vertex{-0.5, 0.0, -0.5, -0.5, 0.0, -0.5});

    mLocalCollisionBox = CollisionBox(QVector2D(-0.5f, 0.5f), QVector2D(0.5f, -0.5f));
}

House::~House() {}

void House::init(GLint matrixUniform[4])
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
void House::draw()
{
    if (renderObject){
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}
