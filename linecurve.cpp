#include "linecurve.h"
#include "math.h"
#include "vertex.h"
#include "renderwindow.h"
#include <stdio.h>

LineCurve::LineCurve(std::string fileName, const int &fNumber)
{
    writeToFile(fileName, fNumber);

    if (mVertices.empty())
    readFile(fileName);

    mMatrix.setToIdentity();
}

LineCurve::~LineCurve() {}

void LineCurve::writeToFile(std::string filename, const int &functionNumber)
{
    switch (functionNumber) {
    case 1:
        lissajous();
        break;
    case 2:
        bezierCurve();
        break;
    case 3:
        leastSquaresMethod();
        break;
    case 4:
        interpolation();
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

void LineCurve::init(GLint matrixUniform[4])
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

void LineCurve::draw()
{
    if (renderObject){
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_LINE_STRIP, 0, mVertices.size());
    }
}

void LineCurve::lissajous()
{
    float z{0};

    for (auto t=0.0f; t<2000.0f; t+=2.0f){
        float xCoord =  sin(t/18);
        float yCoord = cos(t/20);
        mVertices.push_back(Vertex{xCoord,yCoord,z,z,yCoord,xCoord});
    }
}

void LineCurve::bezierCurve()
{
    float z{0};

    for (auto t=0.0f; t<1.0f; t += 0.01f){
        float xCoord = t * 6.0f;
        float yCoord = pow((1 - t), 3.0f) * 0.0f + 3 * pow((1 - t), 2) * t * 5.0f + 3 * (1 - t) * pow(t, 2) * 3.0f + 6.0f * pow(t, 3);
        mVertices.push_back(Vertex{xCoord,yCoord,z,yCoord,xCoord,yCoord*0.5f});
    }
}

void LineCurve::leastSquaresMethod()
{
    float z{0};

    for (auto t=0.0f; t<1.0f; t += 0.01f){
        float xCoord = t * 14.0f;
        float yCoord = -0.02 * pow(xCoord, 2) + 1.16 * xCoord + 0.26;
        mVertices.push_back(Vertex{xCoord,yCoord,z,yCoord,xCoord,z});
    }
}

void LineCurve::interpolation()
{
    float z{0};

    for (auto t= -3.0f; t<13.0f; t += 0.1f){
        float xCoord = t;
        float yCoord = (-0.0521 * pow(xCoord, 3)) + (0.6875 * pow(xCoord, 2)) - (0.6667 * xCoord);
        mVertices.push_back(Vertex{xCoord,yCoord,z,z,yCoord,xCoord});
    }
}

void LineCurve::readFile(std::string fileName)
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
