#include "disc.h"
#include "vertex.h"
#include <math.h>
#include <stdio.h>

// Static member variable
float Disc::t = 0.0f;

Disc::Disc(std::string filnavn)
    : animSpeed{0.01f}, prevDx{0.0f}, prevDy{0.0f}
{
    writeFile(filnavn);

    if(mVertices.empty())
    readFile(filnavn);

    mMatrix.setToIdentity();
}

void Disc::writeFile(std::string filnavn)
{
    construct();

    std::ofstream myFile;
    myFile.open(filnavn.c_str(), std::ofstream::trunc);

    myFile << mVertices.size();
    myFile << std::endl;

    for (auto it = mVertices.begin(); it != mVertices.end(); it++){
        myFile << *it;
        myFile << std::endl;
    }
    myFile.close();
}

Disc::~Disc() {}

void Disc::init(GLint matrixUniform[4])
{
   initializeOpenGLFunctions();

   mMaterial->setActiveShader(ShaderType::PLAIN_SHADER);
   mMaterial->setupModelMatrixUniform(mMatrixUniform, matrixUniform);

   for (GLuint i=0; i<14; i++) mIndices.push_back(i); // Fill up index buffer

   //Vertex Array Object - VAO
   glGenVertexArrays( 1, &mVAO );
   glBindVertexArray( mVAO );

   //Vertex Buffer Object to hold vertices - VBO
   glGenBuffers( 1, &mVBO );
   glBindBuffer( GL_ARRAY_BUFFER, mVBO );
   glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW );

   // 1st attribute buffer : vertices
   glBindBuffer(GL_ARRAY_BUFFER, mVBO);
   glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,sizeof(Vertex), reinterpret_cast<const void*>(0));
   glEnableVertexAttribArray(0);

   // 2nd attribute buffer : colors
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex),  reinterpret_cast<const void*>(3 * sizeof(GLfloat)) );
   glEnableVertexAttribArray(1);

   //enable the matrixUniform
   // mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );
   glGenBuffers(1, &mIBO);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size()*sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);

   glBindVertexArray(0);

}

void Disc::draw()
{
    if (renderObject){
        initializeOpenGLFunctions();
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawElements(GL_TRIANGLE_FAN, mVertices.size(), GL_UNSIGNED_INT, reinterpret_cast<const void*>(0));//mVertices.size());
    }
}

// Konstruerer for TRIANGLE_FAN her
// Hardkodet sektorstørrelse og antall
void Disc::construct()
{
   // Pusher første vertex inn som er senteret i discen. Denne vertexen blir delt med resten av
   // verticeses som blir pusha. Det er fordi glDrawElements() blir kalt med 'GL_TRIANGLE_FAN'
   mVertices.push_back(Vertex{0,0,0,1,1,1});
   for (int i=0; i<13; i++)
   {
       double angle = 30 * i * M_PI / 180;
       float x = cos(angle);
       float y = sin(angle);
       float z = 0.0f;
       float r = i%2;
       float g = 0.f;
       float b = 0.5f;
       mVertices.push_back(Vertex{x,y,z,r,g,b});
   }
}

void Disc::move(float dt)
{
   float degrees = (180 * dt) / M_PI;
   mMatrix.rotate(degrees, 0, 0, 1);
}

void Disc::NpcMovement(const int path)
{
    // 't' = progress into animation (from 0 to 1)
    t += animSpeed;
    if (t >= 1.0f){
        animSpeed *= -1.0f;
    } else if (t <= 0.0f){
        animSpeed *= -1.0f;
    }

    // Call the correct path function
    switch (path) {
    case 1:
        leastSquaresMethodPath(t);
        break;
    case 2:
        interpolationPath(t);
        break;
    default:
        break;
    }
}

void Disc::leastSquaresMethodPath(const float& t)
{
    float dx{ t };
    float dy{ 0 };

    // FILTER (make dx into an actual x-value)
    // path interval is from 0 to 14
    // 't' is now from 0 to 1
    // 't' = 0 should be 0, and 't' = 1 should be 14
    // Homemade equation: max_x - ((max_x + abs(min_x)) * (1 - t)) = 14 - ((14 + 0) * (1 - t)) = 14t
    dx = 14.0f * t;

    // Now as 'dx' is filtered, we can calculate its y-value:
    dy = -0.02f * pow(dx, 2.0f) + 1.16f * dx + 0.26f;

    // SCALE FIXER (because we have scaled both the disc (NPC) and its path, we have to scale the movement accordingly).
    // 0.13f - because 'leastsquaresmethod' path is scaled by 0.13f.
    // 5.0f - because the disc (NPC) is scaled by 0.2f (1.0f / 0.2f = 5.0f)
    dx *= 0.13f * 5.0f;
    dy *= 0.13f * 5.0f;

    mMatrix.translate(dx - prevDx, dy - prevDy, 0.0f);

    prevDx = dx;
    prevDy = dy;
}

void Disc::interpolationPath(const float& t)
{
    float dx{ t };
    float dy{ 0 };

    // FILTER (make dx into an actual x-value)
    // path interval is from -3 to 13
    // 't' is now from 0 to 1
    // 't' = 0 should be -3, and 't' = 1 should be 13
    // Homemade equation: max_x - ((max_x + abs(min_x)) * (1 - t)) = 13 - (16 * (1 - t))
    dx = 13.0f - (16.0f * (1.0f - t));

    // Now as 'dx' is filtered, we can calculate its y-value:
    dy =  -0.0521f * pow(dx, 3.0f) + 0.6875f * pow(dx, 2.0f) - 0.6667f * dx;

    // SCALE FIXER (because we have scaled both the disc (NPC) and its path, we have to scale the movement accordingly).
    // 0.1f - because 'interpolation' path is scaled by 0.1f
    // 5.0f - because the disc (NPC) is scaled by 0.2f (1.0f / 0.2f = 5.0f)
    dx *= 0.1f * 5.0f;
    dy *= 0.1f * 5.0f;

    mMatrix.translate(dx - prevDx, dy - prevDy, 0.0f);

    prevDx = dx;
    prevDy = dy;
}

void Disc::readFile(std::string filnavn)
{
    std::ifstream inn;
    inn.open(filnavn.c_str());

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

void Disc::restartAnimation()
{
    t = 0.0f;
    animSpeed = (animSpeed > 0.0f) ? animSpeed : -animSpeed;
}
