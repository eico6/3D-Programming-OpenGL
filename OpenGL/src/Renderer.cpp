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

void Renderer::Clear() const
{
    CALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    // glDrawArrays()   uses the buffer that is bound at slot 'GL_ARRAY_BUFFER'         = Vertex buffer
    // glDrawElements() uses the buffer that is bound at slot 'GL_ELEMENT_ARRAY_BUFFER' = Index buffer
    CALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}