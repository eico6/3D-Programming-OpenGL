#include "matrix4x4.h"
#include <iostream>
#include <math.h>

Matrix4x4::Matrix4x4()
{
    setToIdentity();
}

void Matrix4x4::setToIdentity()
{
    m[0][0] = 1.0f;
    m[1][0] = 0.0f;
    m[2][0] = 0.0f;
    m[3][0] = 0.0f;
    m[0][1] = 0.0f;
    m[1][1] = 1.0f;
    m[2][1] = 0.0f;
    m[3][1] = 0.0f;
    m[0][2] = 0.0f;
    m[1][2] = 0.0f;
    m[2][2] = 1.0f;
    m[3][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;
}

void Matrix4x4::translate(float x, float y, float z)
{
    float answer[4] {};
    float temp[4]{x, y, z, 1.0f};

    for(int i{0}; i < 4; i++){
        for(int j{0}; j < 4; j++){
            answer[i] += (m[i][j] * temp[j]);
        }
        m[i][3] = answer[i];
    }
}

void Matrix4x4::rotate(float angle, float x, float y, float z)
{
    const float radians{(2 * (float)M_PI) / (360 / angle)};
    float tempMatrix[4][4] {}; // Matrix before rotation

    // Fill up 'tempMatrix'
    for(int i{0}; i < 4; i++){
        for(int j{0}; j < 4; j++){
            tempMatrix[i][j] = m[i][j];
        }
    }

    float xRotation[4][4] = {
         1           ,  0           ,  0           ,  0,
         0           ,  cos(radians), -sin(radians),  0,
         0           ,  sin(radians),  cos(radians),  0,
         0           ,  0           ,  0           ,  1};

    float yRotation[4][4] = {
         cos(radians),  0           ,  sin(radians),  0,
         0           ,  1           ,  0           ,  0,
        -sin(radians),  0           ,  cos(radians),  0,
         0           ,  0           ,  0           ,  1};

    float zRotation[4][4] = {
         cos(radians), -sin(radians),  0           ,  0,
         sin(radians),  cos(radians),  0           ,  0,
         0           ,  0           ,  1           ,  0,
         0           ,  0           ,  0           ,  1};

    if ((abs(x)) > 0.0f){
        for (int j{0}; j < 4; j++){
            for (int i{0}; i < 4; i++){
                m[j][i] = ((tempMatrix[0][i] * xRotation[j][0]) + (tempMatrix[1][i] * xRotation[j][1]) +
                           (tempMatrix[2][i] * xRotation[j][2]) + (tempMatrix[3][i] * xRotation[j][3])) * x;
            }
        }
        // Fill up 'tempMatrix'
        for(int i{0}; i < 4; i++){
            for(int j{0}; j < 4; j++){
                tempMatrix[i][j] = m[i][j];
            }
        }
    }

    if ((abs(y)) > 0.0f){
        for (int j{0}; j < 4; j++){
            for (int i{0}; i < 4; i++){
                m[j][i] = ((tempMatrix[0][i] * yRotation[j][0]) + (tempMatrix[1][i] * yRotation[j][1]) +
                           (tempMatrix[2][i] * yRotation[j][2]) + (tempMatrix[3][i] * yRotation[j][3])) * y;
            }
        }
        // Fill up 'tempMatrix'
        for(int i{0}; i < 4; i++){
            for(int j{0}; j < 4; j++){
                tempMatrix[i][j] = m[i][j];
            }
        }
    }

    if ((abs(z)) > 0.0f){
        for (int j{0}; j < 4; j++){
            for (int i{0}; i < 4; i++){
                m[j][i] = ((tempMatrix[0][i] * zRotation[j][0]) + (tempMatrix[1][i] * zRotation[j][1]) +
                           (tempMatrix[2][i] * zRotation[j][2]) + (tempMatrix[3][i] * zRotation[j][3])) * z;
            }
        }
        // Fill up 'tempMatrix'
        for(int i{0}; i < 4; i++){
            for(int j{0}; j < 4; j++){
                tempMatrix[i][j] = m[i][j];
            }
        }
    }
}

void Matrix4x4::scale(float x, float y, float z)
{
    float tempMatrix[4][4] {}; // Matrix before scaling

    // Fill up 'tempMatrix'
    for(int i{0}; i < 4; i++){
        for(int j{0}; j < 4; j++){
            tempMatrix[i][j] = m[i][j];
        }
    }

    float scalingMatrix[4][4] = {
         x           ,  0           ,  0           ,  0,
         0           ,  y           ,  0           ,  0,
         0           ,  0           ,  z           ,  0,
         0           ,  0           ,  0           ,  1};

    if ((abs(x)) > 0.0f || (abs(y)) > 0.0f || (abs(z)) > 0.0f){
        for (int j{0}; j < 4; j++){
            for (int i{0}; i < 4; i++){
                m[j][i] = (tempMatrix[0][i] * scalingMatrix[j][0]) + (tempMatrix[1][i] * scalingMatrix[j][1]) +
                          (tempMatrix[2][i] * scalingMatrix[j][2]) + (tempMatrix[3][i] * scalingMatrix[j][3]);
            }
        }
    }
}

void Matrix4x4::printMatrix()
{
    std::cout << std::endl << "Matrix:" << std::endl;
    for(int i{0}; i < 4; i++){
        for(int j{0}; j < 4; j++){
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
