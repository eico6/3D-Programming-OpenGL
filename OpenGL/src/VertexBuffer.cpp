#include "VertexBuffer.h"

#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
    : m_RendererID{}
{
    // Generate '1' buffer, and store the buffer's ID in 'm_RendererID'
    CALL(glGenBuffers(1, &m_RendererID));              

    // "Place" this buffer at the 'GL_ARRAY_BUFFER' slot (used by vertex buffers)
    CALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); 

    // Fill up buffer bound at slot 'GL_ARRAY_BUFFER' with the contents of 'data'.
    CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    CALL(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
    CALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
