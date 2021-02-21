#include "VertexArray.h"

#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
    CALL(glGenVertexArrays(1, &m_RendererID)); 
}

VertexArray::~VertexArray()
{
    CALL(glDeleteVertexArrays(1, &m_RendererID));
}
   
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
	vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        // Enables the attribute at index 0. Disabled attributes will not be used during redering (default)!
        CALL(glEnableVertexAttribArray(i));

        // Tells the GPU how to interpret the data stored in the selected buffer.
        // This information is stored in the current Vertex Array Object (VAO),
        // so it's THIS function that links/connects the buffer stored at 'GL_ARRAY_BUFFER' (VBO) with the current VAO.
        // The function defines only one attribute in the vertex!
        // @index      - The attribute you are defining.
        //               E.g. 0 = position, 1 = color and 2 = UV.
        // @size       - How many objects define this attribute? (not bytes)
        //               E.g. '3' for a 3D vector containing 3 floats.
        // @type       - The type of data the attribute consists of.
        // @normalized - If you want OpenGL to normalize the value for you.
        //               E.g. normalize a (0 - 255) value into a (0 - 1) value.
        // @stride     - The total size of a whole vertex (in bytes).
        //               E.g. a vertex made up of 3 attributes:
        //               position, color and UV = 12 + 8 + 8 = 28 bytes. 
        // @pointer    - Offset from the start of the vertex to current attribute (in bytes).
        //               E.g. '20' if we were defining a UV attribute where there are
        //               first 12 bytes of position attribute and then 8 bytes of color attribute.
        //               Just remember to cast it like this: (const void*)20 
        CALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStirde(), (const void*)offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    CALL(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    CALL(glBindVertexArray(0));
}
