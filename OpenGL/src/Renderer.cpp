#include "Renderer.h"

#include <iostream>

void GLClearError()
{
    // glGetError() will "pop" the last error off the "error queue"
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    // glDebugMessageCallback() is much better way of handling errors in OpenGL
    // GLenum is what glGetError() returns, which is equal to an 'unsigned int'
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << " - line:" << line << std::endl;
        return false;
    }

    return true;
}