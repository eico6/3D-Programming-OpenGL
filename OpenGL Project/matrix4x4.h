#ifndef MATRIX4X4_H
#define MATRIX4X4_H


class Matrix4x4
{
public:
    Matrix4x4();                                         // DONE
    void setToIdentity();                                // DONE
    void translate(float x, float y, float z);           // DONE
    void rotate(float angle, float x, float y, float z); // DONE
    void scale(float x, float y, float z);               // DONE
    void lookAt();                                       // ????
    void printMatrix();
private:
    float m[4][4];
};

#endif // MATRIX4X4_H
