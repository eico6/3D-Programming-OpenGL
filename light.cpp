#include <math.h>

#include "light.h"
#include "renderwindow.h"

Light::Light()
    : animProgress{0.0f}
{
    // Ambient
    mAmbientStrenght = 0.07f;
    mAmbientColor = QVector3D(1.0f, 0.2f, 0.15f);

    // Light
    mLightStrenght = 1.5f;
    mLightColor = QVector3D(0.9f, 0.5f, 0.15f);

    // Specular
    mSpecularStrenght = 1.5f;
    mSpecularExponent = 32;     // higher = smaller spread

    // Attenuation (falloff)
    constant = 1.0f;
    linear = 0.14f;
    quadratic = 0.07f;

//    ********* TABLE FOR ATTENUATION VALUES *********
//    Distance    Constant    Linear    Quadratic
//    7           1.0          0.7	     1.8
//    13          1.0	       0.35	     0.44
//    20          1.0	       0.22	     0.20
//    32          1.0	       0.14	     0.07
//    50          1.0	       0.09	     0.032
//    65          1.0	       0.07	     0.017
//    100         1.0	       0.045	 0.0075
//    160         1.0	       0.027	 0.0028
//    200         1.0	       0.022	 0.0019
//    325         1.0	       0.014	 0.0007
//    600         1.0	       0.007	 0.0002
//    3250        1.0	       0.0014	 0.000007

    // Vertices
    mVertices.insert( mVertices.end(),
    {
        Vertex(-0.25f, -0.25f,  0.25f,    0.8f, 0.8f, 0.3f,     0.f,  0.f),   //Left low
        Vertex( 0.25f, -0.25f,  0.25f,    0.8f, 0.8f, 0.3f,     1.f,  0.f),   //Right low
        Vertex( 0.0f,  0.25f,  0.0f,      0.8f, 0.8f, 0.3f,     0.5f, 0.5f),  //Top
        Vertex( 0.0f, -0.25f, -0.25f,     0.8f, 0.8f, 0.3f,     0.5f, 0.5f)   //Back low
    });

    mIndices.insert( mIndices.end(),
    { 0, 1, 2,
      1, 3, 2,
      3, 0, 2,
      0, 3, 1
    });

    mMatrix.setToIdentity();
}

void Light::init(GLint matrixUniform[4])
{
    initializeOpenGLFunctions();

    // Shader to use
    mMaterial->setActiveShader(ShaderType::PHONG_SHADER);
    mMaterial->setActiveTextureSlot(3);
    mMaterial->setupModelMatrixUniform(mMatrixUniform, matrixUniform);

    //Vertex Array Object - VAO
    glGenVertexArrays( 1, &mVAO );
    glBindVertexArray( mVAO );

    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers( 1, &mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );

    glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW );

    // 1rst attribute buffer : vertices
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex),  (GLvoid*)(3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);

    // 3rd attribute buffer : uvs
    glVertexAttribPointer(2, 2,  GL_FLOAT, GL_FALSE, sizeof( Vertex ), (GLvoid*)( 6 * sizeof( GLfloat ) ));
    glEnableVertexAttribArray(2);

    //Second buffer - holds the indices (Element Array Buffer - EAB):
    glGenBuffers(1, &mEAB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEAB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Light::draw()
{
    if (renderObject){
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, nullptr);
    }

}

void Light::orbitAnimation()
{
    VisualObject::move(sin(animProgress) / 30.0f, 0.0f, cos(animProgress) / 50.0f);
    VisualObject::move(0.0f, cos(animProgress * 4.0f) / 20.0f, 0.0f);
    animProgress += 0.019f;
}

void Light::resetAnimProgress()
{
    animProgress = 0.0f;
}
