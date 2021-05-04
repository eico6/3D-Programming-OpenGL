
#ifndef TEXTURE_H
#define TEXTURE_H

#include <QOpenGLFunctions_4_1_Core>

/**
    \brief Simple class for creating textures from a bitmap file.
    \author Dag Nylund
    \date 16/02/05
 */
class Texture : protected QOpenGLFunctions_4_1_Core
{
public:
    Texture();  //basic texture from code
    Texture(const std::string &filename);
    inline GLuint id() const { return mId; }
    std::string textureFilename;

    // Heightmap
    inline int getColumns() const           { return mColumns; }
    inline int getRows() const              { return mRows; }
    inline int getBytesPrPixel() const      { return mBytesPrPixel; }
    inline unsigned char* getBitmap() const { return mBitmap; }

private:
    GLubyte pixels[16];     // For the standard texture from the no-parameter constructor
    GLuint mId{0};          //Texture ID that OpenGL makes when glGenTextures is called
    int mColumns;
    int mRows;
    int mBytesPrPixel;
    bool mAlphaUsed{false};
    void readBitmap(const std::string& filename);
    void setTexture();
    unsigned char *mBitmap;

private:
    //this is put inside this class to avoid spamming the main namespace
    //with stuff that only is used inside this class

    //Quick fix to get rid of windows.h which contains
    //BITMAPINFOHEADER and BITMAPFILEHEADER.
    typedef unsigned short int OWORD;    //should be 16 bit
    typedef unsigned int ODWORD;         //should be 32 bit
    typedef int OLONG;                   //should be 32 bit

    struct OBITMAPINFOHEADER {
        ODWORD biSize;
        OLONG  biWidth;
        OLONG  biHeight;
        OWORD  biPlanes;
        OWORD  biBitCount;
        ODWORD biCompression;
        ODWORD biSizeImage;
        OLONG  biXPelsPerMeter;
        OLONG  biYPelsPerMeter;
        ODWORD biClrUsed;
        ODWORD biClrImportant;
    };

    struct OBITMAPFILEHEADER {
        OWORD  bfType;
        ODWORD bfSize;
        OWORD  bfReserved1;
        OWORD  bfReserved2;
        ODWORD bfOffBits;
    };
};

#endif // TEXTURE_H
