#ifndef CAMERA_H
#define CAMERA_H

#include <QOpenGLFunctions_4_1_Core>
#include <QVector3D>
#include <QMatrix4x4>

class Camera : public QOpenGLFunctions_4_1_Core
{
public:
    Camera(int modeInput);
    ~Camera() { }
    void init();
    void update(GLint pMatrixUniform, GLint vMatrixUniform);
    void perspective(int degrees, double aspect, double nearplane, double farplane);
    void lookAt(const QVector3D& eye, const QVector3D& at, const QVector3D& up);
    void setEyePos(QVector3D newPos);
    void setEyePos(float x, float y, float z);
    inline const QVector3D getEyePos() { return QVector3D(mEye.x(), mEye.y(), mEye.z()); }

    void setSpeed(float speed);
    void moveRight(float delta);

private:
    int cameraType;

    QVector3D mForward {0.f, 0.f, -1.f};
    QVector3D mRight   {1.f, 0.f,  0.f};

    QVector3D mEye;
    float mSpeed{0.0f};

    QMatrix4x4 mPmatrix;
    QMatrix4x4 mVmatrix;
};


#endif // CAMERA_H
