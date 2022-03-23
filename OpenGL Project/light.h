#ifndef LIGHT_H
#define LIGHT_H

#include "visualobject.h"

class Light : public VisualObject
{
public:
    Light();
    virtual void init(GLint matrixUniform[4]) override;
    virtual void draw() override;

    // Ambient
    GLfloat mAmbientStrenght;
    QVector3D mAmbientColor;

    // Light
    GLfloat mLightStrenght;
    QVector3D mLightColor;

    // Specular
    GLfloat mSpecularStrenght;
    GLint mSpecularExponent;

    // Attenuation (falloff)
    GLfloat constant;
    GLfloat linear;
    GLfloat quadratic;

    void orbitAnimation();
    void resetAnimProgress();
private:
    // These should be in all VisualObjects, if they are, delete these
    std::vector<GLuint> mIndices;
    GLuint mEAB{0};

    float animProgress;
};

#endif // LIGHT_H
