#include <QDebug>
#include <QImage>
#include <QBuffer>
#include <QByteArray>

#include <iostream>
#include <fstream>
#include <string>

#include "texture.h"

Texture::Texture()
{
    initializeOpenGLFunctions();
    //small dummy texture
    for (int i=0; i<16; i++)
        pixels[i] = 0;
    pixels[0] = 255;
    pixels[4] = 255;
    pixels[8] = 255;
    pixels[9] = 255;
    pixels[10] = 255;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);
    qDebug() << "Texture default: id = " << mId;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 reinterpret_cast<const GLvoid*>(pixels));
}

/**
 \brief Texture::Texture() Read a bitmap file and create a texture with standard parameters
 \param filename The name of the bmp file containing a texture
 First one 2D texture is generated from
 - glGenTextures()
 Then the OpenGL functions
 - glBindTexture()
 - glTexParameteri()
 - glTexImage2D()
 are used. The texture can be retrieved later by using the function id()
 */
Texture::Texture(const std::string& filename): QOpenGLFunctions_4_1_Core()
{
    textureFilename = filename;
    initializeOpenGLFunctions();
    readBitmap(filename);       //reads the BMP into memory
    setTexture();               //set texture up for OpenGL
}

/**
    \brief Texture::id() Return the id of a previously generated texture object
    \return The id of a previously generated texture object
 */

//Read BMP into memory
void Texture::readBitmap(const std::string &filename)
{
    OBITMAPFILEHEADER bmFileHeader;
    OBITMAPINFOHEADER bmInfoHeader;

    std::string fileWithPath = filename;

    std::ifstream file;
    file.open (fileWithPath.c_str(), std::ifstream::in | std::ifstream::binary);
    if (file.is_open())
    {
        file.read((char *) &bmFileHeader, 14);

        file.read((char *) &bmInfoHeader, sizeof(OBITMAPINFOHEADER));
        mColumns = bmInfoHeader.biWidth;
        mRows = bmInfoHeader.biHeight;
        mBytesPrPixel = bmInfoHeader.biBitCount / 8;
        if(mBytesPrPixel == 4)
            mAlphaUsed = true;

        mBitmap = new unsigned char[mColumns * mRows * mBytesPrPixel];
        file.read((char *) mBitmap, mColumns * mRows * mBytesPrPixel);
        file.close();
    }
    else
    {
        qDebug() << "ERROR: Can not read " << QString(fileWithPath.c_str());
    }
}

//Set up texture for use in OpenGL
void Texture::setTexture()
{
    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);
    qDebug() << "Texture" << textureFilename.c_str() << "successfully read | id = " << mId << "| bytes pr pixel:" << mBytesPrPixel << "| using alpha:" << mAlphaUsed;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    if(mAlphaUsed == false)             //no alpha in this bmp
        glTexImage2D(
                    GL_TEXTURE_2D,
                    0,                  //mipmap level
                    GL_RGB,             //internal format - what format should OpenGL use
                    mColumns,
                    mRows,
                    0,                  //always 0
                    GL_BGR,             //format of data from texture file -  bmp uses BGR, not RGB
                    GL_UNSIGNED_BYTE,   //size of each color channel
                    mBitmap);           //pointer to texture in memory

    else                                //alpha is present, so we set up an alpha channel
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mColumns, mRows, 0,  GL_BGRA, GL_UNSIGNED_BYTE, mBitmap);

    glGenerateMipmap(GL_TEXTURE_2D);
}
