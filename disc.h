#ifndef DISC_H
#define DISC_H

#include "visualobject.h"

class Disc : public VisualObject
{
public:
    Disc(std::string filnavn);
    ~Disc() override;
    void readFile(std::string filnavn);
    void writeFile(std::string filnavn);
    void init(GLint matrixUniform[4]) override;
    void draw() override;
    void construct();
    void move(float dt) override;
    void NpcMovement(const int path); // Currently using the disc as the NPC
    void restartAnimation();
protected:
    std::vector<GLuint> mIndices;
    GLuint mIBO{0};

    float mRadius{0.5};
//    QVector4D mRotation;   // What?? Koffor 2 av samme? (sjekk parent)
private:
    // Time into 'NpcMovement()' animation
    static float t;
    float animSpeed;
    float prevDx, prevDy;
    void leastSquaresMethodPath(const float& t);
    void interpolationPath(const float& t);
};

#endif // DISC_H
