#include "grid.h"

Grid::Grid()
{
    // This variable 'increments' is used both along the X-axis and the Z-axis.
    // This will unsure a symmetric, perfectly quadratic, grid.
    // The amount of lines produced (higher values will increase density).
    const int increments{24};

    // ------------------------------------------------------------------------------------------
    // GRID LINES ALONG THE X-AXIS
    // ------------------------------------------------------------------------------------------
    const float xFromPosition{-15.0f}; // Starting x-coordinate of a grid's line.
    const float xToPosition{15.0f};    // Ending x-coordinate of a grid's line.
    const float xDivider{1.25f};       // Length between each line. Is equal to total length divided by increments.
                                       // Equals: (abs(xFromPosition) + xToPosition) / increments
                                       // Value is hardcoded to retain readability.

    // These two first vertices pushed are the vertices that create the line that intersects origo.
    // I put these outside of the for-loop as I want this line to be darker in color than the rest.
    mVertices.push_back(Vertex{xFromPosition, 0.0f, 0.0f,      0.1f, 0.1f, 0.1f});
    mVertices.push_back(Vertex{xToPosition,   0.0f, 0.0f,      0.1f, 0.1f, 0.1f});

    // This for-loop pushes vertices in pair. These vertices produce lines parallell to the x-axis.
    // @ The first vertex pushed              = the line's start position.
    // @ The second vertex pushed             = the line's end position.
    // @ Last three floats in each vertex     = the line's color.
    // @ Z-coordinate of each vertex          = (xDivider * i) will advance the line 'i' times/steps. Then (- xToPosition) will offset the line to origo.
    for(int i{0}; i <= increments; i++){
        mVertices.push_back(Vertex{xFromPosition, 0.0f, (xDivider * i) - xToPosition,     0.4f, 0.4f, 0.4f});
        mVertices.push_back(Vertex{xToPosition,   0.0f, (xDivider * i) - xToPosition,     0.4f, 0.4f, 0.4f});
    }


    // ------------------------------------------------------------------------------------------
    // GRID LINES ALONG THE Z-AXIS
    // ------------------------------------------------------------------------------------------
    const float zFromPosition{-15.0f}; // Starting z-coordinate of a grid's line.
    const float zToPosition{15.0f};    // Ending z-coordinate of a grid's line.
    const float zDivider{1.25f};       // Length between each line. Is equal to total length divided by increments.
                                       // Equals: (abs(zFromPosition) + zToPosition) / increments
                                       // Value is hardcoded to retain readability.

    // These two first vertices pushed are the vertices that create the line that intersects origo.
    // I put these outside of the for-loop as I want this line to be darker in color than the rest.
    mVertices.push_back(Vertex{0.0f, 0.0f, zFromPosition,      0.1f, 0.1f, 0.1f});
    mVertices.push_back(Vertex{0.0f, 0.0f, zToPosition,        0.1f, 0.1f, 0.1f});

    // This for-loop pushes vertices in pair. These vertices produce lines parallell to the z-axis.
    // @ The first vertex pushed              = the line's start position.
    // @ The second vertex pushed             = the line's end position.
    // @ Last three floats in each vertex     = the line's color.
    // @ X-coordinate of each vertex          = (zDivider * i) will advance the line 'i' times/steps. Then (- zToPosition) will offset the line to origo.
    for(int i{0}; i <= increments; i++){
        mVertices.push_back(Vertex{(zDivider * i) - zToPosition, 0.0f, zFromPosition,     0.4f, 0.4f, 0.4f});
        mVertices.push_back(Vertex{(zDivider * i) - zToPosition, 0.0f, zToPosition,       0.4f, 0.4f, 0.4f});
    }

    mMatrix.setToIdentity();
}

Grid::~Grid() {}

void Grid::init(GLint matrixUniform[4])
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

void Grid::draw()
{
    if (renderObject){
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_LINES, 0, mVertices.size());
    }
}
