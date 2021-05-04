#include "cube.h"

Cube::Cube()
    : InteractiveObject(), cameraOffset{QVector3D(0.0f, 0.0f, -1.5f)}
{
                                 // Positions             // Colors          // UV
    mVertices.push_back(Vertex{-0.5f, -0.5f,  0.5f,    0.3f, 0.0f, 0.5f,    0.0f, 0.0f});
    mVertices.push_back(Vertex{ 0.5f, -0.5f,  0.5f,    0.5f, 0.2f, 0.6f,    1.0f, 0.0f});
    mVertices.push_back(Vertex{-0.5f,  0.5f,  0.5f,    0.5f, 0.2f, 0.6f,    0.0f, 1.0f});

    mVertices.push_back(Vertex{ 0.5f,  0.5f,  0.5f,    0.7f, 0.0f, 0.3f,    1.0f, 1.0f});
    mVertices.push_back(Vertex{-0.5f,  0.5f,  0.5f,    0.5f, 0.2f, 0.6f,    0.0f, 1.0f});
    mVertices.push_back(Vertex{ 0.5f, -0.5f,  0.5f,    0.5f, 0.2f, 0.6f,    1.0f, 0.0f});

    mVertices.push_back(Vertex{ 0.5f, -0.5f,  0.5f,    0.3f, 0.0f, 0.5f,    0.0f, 0.0f});
    mVertices.push_back(Vertex{ 0.5f, -0.5f, -0.5f,    0.5f, 0.2f, 0.6f,    1.0f, 0.0f});
    mVertices.push_back(Vertex{ 0.5f,  0.5f,  0.5f,    0.5f, 0.2f, 0.6f,    0.0f, 1.0f});

    mVertices.push_back(Vertex{ 0.5f,  0.5f, -0.5f,    0.7f, 0.0f, 0.3f,    1.0f, 1.0f});
    mVertices.push_back(Vertex{ 0.5f,  0.5f,  0.5f,    0.5f, 0.2f, 0.6f,    0.0f, 1.0f});
    mVertices.push_back(Vertex{ 0.5f, -0.5f, -0.5f,    0.5f, 0.2f, 0.6f,    1.0f, 0.0f});

    mVertices.push_back(Vertex{ 0.5f, -0.5f, -0.5f,    0.3f, 0.0f, 0.5f,    0.0f, 0.0f});
    mVertices.push_back(Vertex{-0.5f, -0.5f, -0.5f,    0.5f, 0.2f, 0.6f,    1.0f, 0.0f});
    mVertices.push_back(Vertex{ 0.5f,  0.5f, -0.5f,    0.5f, 0.2f, 0.6f,    0.0f, 1.0f});

    mVertices.push_back(Vertex{-0.5f,  0.5f, -0.5f,    0.7f, 0.0f, 0.3f,    1.0f, 1.0f});
    mVertices.push_back(Vertex{ 0.5f,  0.5f, -0.5f,    0.5f, 0.2f, 0.6f,    0.0f, 1.0f});
    mVertices.push_back(Vertex{-0.5f, -0.5f, -0.5f,    0.5f, 0.2f, 0.6f,    1.0f, 0.0f});

    mVertices.push_back(Vertex{-0.5f, -0.5f, -0.5f,    0.3f, 0.0f, 0.5f,    0.0f, 0.0f});
    mVertices.push_back(Vertex{-0.5f, -0.5f,  0.5f,    0.5f, 0.2f, 0.6f,    1.0f, 0.0f});
    mVertices.push_back(Vertex{-0.5f,  0.5f, -0.5f,    0.5f, 0.2f, 0.6f,    0.0f, 1.0f});

    mVertices.push_back(Vertex{-0.5f,  0.5f,  0.5f,    0.7f, 0.0f, 0.3f,    1.0f, 1.0f});
    mVertices.push_back(Vertex{-0.5f,  0.5f, -0.5f,    0.5f, 0.2f, 0.6f,    0.0f, 1.0f});
    mVertices.push_back(Vertex{-0.5f, -0.5f,  0.5f,    0.5f, 0.2f, 0.6f,    1.0f, 0.0f});

    mVertices.push_back(Vertex{-0.5f, -0.5f, -0.5f,    0.3f, 0.0f, 0.5f,    0.0f, 0.0f});
    mVertices.push_back(Vertex{ 0.5f, -0.5f, -0.5f,    0.5f, 0.2f, 0.6f,    1.0f, 0.0f});
    mVertices.push_back(Vertex{-0.5f, -0.5f,  0.5f,    0.5f, 0.2f, 0.6f,    0.0f, 1.0f});

    mVertices.push_back(Vertex{ 0.5f, -0.5f,  0.5f,    0.7f, 0.0f, 0.3f,    1.0f, 1.0f});
    mVertices.push_back(Vertex{-0.5f, -0.5f,  0.5f,    0.5f, 0.2f, 0.6f,    0.0f, 1.0f});
    mVertices.push_back(Vertex{ 0.5f, -0.5f, -0.5f,    0.5f, 0.2f, 0.6f,    1.0f, 0.0f});

    mVertices.push_back(Vertex{-0.5f,  0.5f,  0.5f,    0.3f, 0.0f, 0.5f,    0.0f, 0.0f});
    mVertices.push_back(Vertex{ 0.5f,  0.5f,  0.5f,    0.5f, 0.2f, 0.6f,    1.0f, 0.0f});
    mVertices.push_back(Vertex{-0.5f,  0.5f, -0.5f,    0.5f, 0.2f, 0.6f,    0.0f, 1.0f});

    mVertices.push_back(Vertex{ 0.5f,  0.5f, -0.5f,    0.7f, 0.0f, 0.3f,    1.0f, 1.0f});
    mVertices.push_back(Vertex{-0.5f,  0.5f, -0.5f,    0.5f, 0.2f, 0.6f,    0.0f, 1.0f});
    mVertices.push_back(Vertex{ 0.5f,  0.5f,  0.5f,    0.5f, 0.2f, 0.6f,    1.0f, 0.0f});

    mLocalCollisionBox = CollisionBox(QVector2D(-0.5f, 0.5f), QVector2D(0.5f, -0.5f));

    mMatrix.setToIdentity();

    cameraTarget = getPos() + cameraOffset;
}

Cube::~Cube() {}

void Cube::init(GLint matrixUniform[4])
{
    initializeOpenGLFunctions();

    // Set what shader you want to use to render this object
    mMaterial->setActiveShader(ShaderType::PHONG_SHADER);
    mMaterial->setActiveTextureSlot(2);
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

    // 1rst attribute buffer : coordinates
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(0));
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex),  reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);

    // 3rd attribute buffer : uvs
    glVertexAttribPointer(2, 2,  GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)( 6 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Cube::draw()
{
    if (renderObject){
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}

void Cube::move(float dx, float dy, float dz)
{
    InteractiveObject::move(dx, dy + 0.08f, dz);

    cameraTarget = getPos() + cameraOffset;
}

void Cube::moveInHouse(float dx, float dz)
{
    // semi-hardcode translation in comparison to 'Cube::move()'
    mPosition.setColumn(3, mPosition.column(3)+QVector4D(dx, 0, dz, 0));
    mMatrix.translate(dx*5.0f, 0.0f, dz*5.0f);

    // Converts objetc's collision box from local- to world space
    if (mLocalCollisionBox.collisionBoxIsActive())
        convertCollision();
}
