#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "visualobject.h"
#include <vertex.h>
#include "texture.h"

class Heightmap : public VisualObject
{
public:
    Heightmap(std::string fileName);
    ~Heightmap() override;

    void init(GLint matrixUniform[3]) override;
    void draw() override;
    void constructHeightmap();

private:
    Texture* HMTexture{nullptr};
    unsigned char* mBitmap;
};

#endif // HEIGHTMAP_H
