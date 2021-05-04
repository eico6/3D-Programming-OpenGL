#include "vertex.h"
#include "trianglesurface.h"
#include "renderwindow.h"
#include <math.h>
#include <stdio.h>


TriangleSurface::TriangleSurface(std::string fileName, const float &xmin, const float &xmax, const float &zmin,
                                 const float &zmax, const float &hIn, const int &fNumber) : VisualObject()
{
    // Save parameters so I don't need to pass it into all methods
    xMin = xmin;
    xMax = xmax;
    zMin = zmin;
    zMax = zmax;
    h = hIn;
    functionNumber = fNumber;

    writeToFile(fileName);
    readFile(fileName);
    mMatrix.setToIdentity();
}

TriangleSurface::~TriangleSurface() {}

void TriangleSurface::writeToFile(std::string filename)
{
    bool bFileExists = true;
    std::ifstream infile(filename);
    bFileExists = infile.good();

    if(!bFileExists) {
        switch (functionNumber) {
        case 1:
            sinCos();
            break;
        default:
            // Ugyldig 'functionNumber'
            break;
        }

        std::ofstream myFile;
        myFile.open(filename.c_str(), std::ofstream::trunc);

        myFile << mVertices.size();
        myFile << std::endl;

        for (auto it = mVertices.begin(); it != mVertices.end(); it++){
            myFile << *it;
            myFile << std::endl;
        }

        myFile.close();
    }
}

void TriangleSurface::init(GLint matrixUniform[4])
{
    initializeOpenGLFunctions();

    mMaterial->setActiveShader(ShaderType::PLAIN_SHADER);
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

void TriangleSurface::draw()
{
    if (renderObject){
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}

void TriangleSurface::sinCos()
{
    float stretchVar{0.3f};
    float altitudeVar{0.8f};

    for (auto x=xMin; x<xMax - h; x+=h)
        for (auto z=zMin; z<zMax - h; z+=h)
        {
            // Function value
            float y{};

            // ********************************       UV       ********************************
            const float u{(x + abs(xMin)) / (xMax + abs(xMin) + (h * 15.0f))};
            const float v{(z + abs(zMin)) / (zMax + abs(zMin) + (h * 15.0f))};


            // ******************************** NORMAL VECTORS ********************************
            // Points
            y = sin(M_PI*x*stretchVar)*cos(M_PI*z*stretchVar)*altitudeVar;
            QVector3D p1(x, y, z);
            y = sin(M_PI*(x+h)*stretchVar)*cos(M_PI*z*stretchVar)*altitudeVar;
            QVector3D p2(x+h, y, z);
            y = sin(M_PI*x*stretchVar)*cos(M_PI*(z+h)*stretchVar)*altitudeVar;
            QVector3D p3(x, y, z+h);
            y = sin(M_PI*(x+h)*stretchVar)*cos(M_PI*(z+h)*stretchVar)*altitudeVar;
            QVector3D p4(x+h, y, z+h);

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
            y = sin(M_PI*x*stretchVar)*cos(M_PI*z*stretchVar)*altitudeVar;
            mVertices.push_back(Vertex{x,y,z,n1.x(),n1.y(),n1.z(),u,v});
            y = sin(M_PI*(x+h)*stretchVar)*cos(M_PI*z*stretchVar)*altitudeVar;
            mVertices.push_back(Vertex{x+h,y,z,n2.x(),n2.y(),n2.z(),u+h,v});
            y = sin(M_PI*x*stretchVar)*cos(M_PI*(z+h)*stretchVar)*altitudeVar;
            mVertices.push_back(Vertex{x,y,z+h,n1.x(),n1.y(),n1.z(),u,v+h});
            mVertices.push_back(Vertex{x,y,z+h,n1.x(),n1.y(),n1.z(),u,v+h});
            y = sin(M_PI*(x+h)*stretchVar)*cos(M_PI*z*stretchVar)*altitudeVar;
            mVertices.push_back(Vertex{x+h,y,z,n2.x(),n2.y(),n2.z(),u+h,v});
            y = sin(M_PI*(x+h)*stretchVar)*cos(M_PI*(z+h)*stretchVar)*altitudeVar;
            mVertices.push_back(Vertex{x+h,y,z+h,n2.x(),n2.y(),n2.z(),u+h,v+h});
        }
}

void TriangleSurface::readFile(std::string fileName)
{
    std::ifstream inn;
    inn.open(fileName.c_str());

    if (inn.is_open()) {
        int n;
        Vertex vertex;
        inn >> n;
        mVertices.reserve(n);
        for (int i=0; i<n; i++) {
             inn >> vertex;
             mVertices.push_back(vertex);
        }
        inn.close();
    }
}



