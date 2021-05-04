#include "camera.h"
#include <cmath>

Camera::Camera(int modeInput)
    : mEye{1.5, 3.0, 2.0}
{
    mPmatrix.setToIdentity();
    mVmatrix.setToIdentity();

    cameraType = modeInput;
}

void Camera::init()
{
    mPmatrix.setToIdentity();
    mVmatrix.setToIdentity();
}

void Camera::update(GLint pMatrixUniform, GLint vMatrixUniform)
{
    initializeOpenGLFunctions();

    if (cameraType == 1){ // 1 = 'EDIT_MODE'
        mEye -= mForward * mSpeed;
        mSpeed = 0.0f;
        lookAt(mEye, QVector3D(0.0f, 0.0f, 0.0f), QVector3D{0,1,0});
    }

    glUniformMatrix4fv(pMatrixUniform,1, GL_FALSE, mPmatrix.constData());
    glUniformMatrix4fv(vMatrixUniform,1, GL_FALSE, mVmatrix.constData());
}

void Camera::moveRight(float delta)
{
    mEye += mRight * delta;
}

void Camera::perspective(int degrees, double aspect, double nearplane, double farplane)
{
    mPmatrix.perspective(degrees, aspect, nearplane, farplane);
}

void Camera::lookAt(const QVector3D &eye, const QVector3D &at, const QVector3D &up)
{
    mVmatrix.setToIdentity();
    mEye = eye;
    mVmatrix.lookAt(eye, at, up);
}

void Camera::setEyePos(QVector3D newPos)
{
    mEye = newPos;
}

void Camera::setEyePos(float x, float y, float z)
{
    mEye = QVector3D(x,y,z);
}

void Camera::setSpeed(float speed)
{
    mSpeed = speed;
}



