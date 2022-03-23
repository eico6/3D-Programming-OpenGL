#include "heightmap.h"
#include <math.h>

Heightmap::Heightmap(std::string fileName)
{
    HMTexture = new Texture(fileName);

    //readFromBitmap();
    constructHeightmap();
}

Heightmap::~Heightmap() {}

void Heightmap::init(GLint matrixUniform[])
{
    initializeOpenGLFunctions();

    mMaterial->setActiveShader(ShaderType::PHONG_SHADER);
    mMaterial->setActiveTextureSlot(1);
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

    glVertexAttribPointer(2, 2,  GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)( 6 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Heightmap::draw()
{
    if (renderObject){
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}

void Heightmap::constructHeightmap()
{
    // The height of each point
    float y{};

    // Retrieve data
    mBitmap = HMTexture->getBitmap();
    const int bytesize{ HMTexture->getBytesPrPixel() };
    const int columns{ HMTexture->getColumns() };

    // Dimensions
    const float xMax{40.f}, xMin{0.f}, zMax{40.0f}, zMin{0.f};
    const float xOffset{-7.0f};
    const float yOffset{-0.7f};
    const float zOffset{-7.0f};

    // Scaling
    const float t{1.0f};               // space between each vertex
    const float stretchScale{0.35f};   // scales the map's x and z
    const float heightScale{0.009f};   // scales the map's y

    for (float x = zMin; x < zMax; x += 1.0f) {
        for (float z = xMin; z < xMax; z += 1.0f) {


            // ********************************       UV       ********************************
            const float u{(x + abs(xMin)) / (xMax + abs(xMin) + (stretchScale * 15.0f))};
            const float v{(z + abs(zMin)) / (zMax + abs(zMin) + (stretchScale * 15.0f))};


            // ******************************** NORMAL VECTORS ********************************
            // Points
            y = mBitmap[(int)((z * 256) + x) * bytesize] * heightScale;
            const QVector3D p1(x, y, z);
            y = mBitmap[(int)((z * 256) + x + 1) * bytesize] * heightScale;
            const QVector3D p2(x + stretchScale, y, z);
            y = mBitmap[(int)((z * 256) + x) * bytesize + columns * bytesize] * heightScale;
            const QVector3D p3(x, y, z + stretchScale);
            y = mBitmap[(int)((z * 256) + x + 1) * bytesize + columns * bytesize] * heightScale;
            const QVector3D p4(x + stretchScale, y, z + stretchScale);

            // Normal 1
            QVector3D vec1 = (p1 - p2);
            QVector3D vec2 = (p1 - p3);
            QVector3D n1 = -QVector3D::crossProduct(vec1, vec2);
            n1.normalize();

            // Normal 2
            QVector3D vec3 = (p4 - p2);
            QVector3D vec4 = (p4 - p3);
            QVector3D n2 = QVector3D::crossProduct(vec3, vec4);
            n2.normalize();


            // ********************************  INSERTION  ********************************
            // Top-Left
            y = (mBitmap[(int)((z * 256) + x) * bytesize] * heightScale) + yOffset;
            mVertices.push_back(Vertex{(x * stretchScale) + xOffset, y, (z * stretchScale) + zOffset,
                                       n1.x(), n1.y(), n1.z(),
                                       u, v});

            // Top-Right
            y = (mBitmap[(int)((z * 256) + x + 1) * bytesize] * heightScale) + yOffset;
            mVertices.push_back(Vertex{((x + t) * stretchScale) + xOffset, y, (z * stretchScale) + zOffset,
                                       n2.x(), n2.y(), n2.z(),
                                       u + stretchScale, v});

            // Bot-Left
            y = (mBitmap[(int)((z * 256) + x) * bytesize + columns * bytesize] * heightScale) + yOffset;
            mVertices.push_back(Vertex{(x * stretchScale) + xOffset, y, ((z + t) * stretchScale) + zOffset,
                                       n1.x(), n1.y(), n1.z(),
                                       u, v + stretchScale});

            // Bot-Left
            y = (mBitmap[(int)((z * 256) + x) * bytesize + columns * bytesize] * heightScale) + yOffset;
            mVertices.push_back(Vertex{(x * stretchScale) + xOffset, y, ((z + t) * stretchScale) + zOffset,
                                       n1.x(), n1.y(), n1.z(),
                                       u, v + stretchScale});

            // Top-Right
            y = (mBitmap[(int)((z * 256) + x + 1) * bytesize] * heightScale) + yOffset;
            mVertices.push_back(Vertex{((x + t) * stretchScale) + xOffset, y, (z * stretchScale) + zOffset,
                                       n2.x(), n2.y(), n2.z(),
                                       u + stretchScale, v});

            // Bot-Right
            y = (mBitmap[(int)((z * 256) + x + 1) * bytesize + columns * bytesize] * heightScale) + yOffset;
            mVertices.push_back(Vertex{((x + t) * stretchScale) + xOffset, y, ((z + t) * stretchScale) + zOffset,
                                       n2.x(), n2.y(), n2.z(),
                                       u + stretchScale, v + stretchScale});

        }
    }
}
