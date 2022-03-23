#ifndef LINECURVE_H
#define LINECURVE_H

#include "visualobject.h"

class LineCurve : public VisualObject
{
public:
    LineCurve(std::string fileName, const int &fNumber);
    ~LineCurve() override;

    void writeToFile(std::string filename, const int &functionNumber);
    void init(GLint matrixUniform[4]) override;
    void draw() override;
    void readFile(std::string fileName);

private:
    void lissajous();
    void bezierCurve();
    void leastSquaresMethod();
    void interpolation();

    std::vector <Vertex> mVertices;
};

#endif // LINECURVE_H
