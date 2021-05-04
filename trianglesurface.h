#include <iostream>
#include <vector>
#include <vertex.h>
#include <visualobject.h>

#ifndef TRIANGLESURFACE_H
#define TRIANGLESURFACE_H


class TriangleSurface : public VisualObject
{
public:
    TriangleSurface(std::string fileName, const float &xmin, const float &xmax, const float &zmin,
                    const float &zmax, const float &hIn, const int &fNumber);
    ~TriangleSurface() override;
    void writeToFile(std::string filename);
    void init(GLint matrixUniform[4]) override;
    void draw() override;
    void readFile(std::string fileName);

private:
    void sinCos();

    float xMin{}, xMax{}, zMin{}, zMax{}, h{};
    int functionNumber{};
};

#endif // TRIANGLESURFACE_H
