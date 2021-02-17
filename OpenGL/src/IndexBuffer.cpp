#include "IndexBuffer.h"

#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count), m_RendererID{}
{
    // Make sure that 'GLuint' is actually the same size as an 'unsigned int' 
    ASSERT(sizeof(unsigned int) == sizeof(GLuint)); 

    // Generate '1' buffer, and store the buffer's ID in 'm_RendererID'
    CALL(glGenBuffers(1, &m_RendererID));              

    // "Place" this buffer at the 'GL_ELEMENT_ARRAY_BUFFER' slot (used by index buffers)
    CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); 

    // Fill up buffer bound at slot 'GL_ELEMENT_ARRAY_BUFFER' with the contents of 'data'.
    CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() 
{
    CALL(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
    CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
    CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
