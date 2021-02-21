#pragma once

#include <Gl/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

// 'ASSERT(x)' will be replaced with 'if (!(x)) __debugbreak();' at compilation.
// '__debugbreak()' is compiler spesific code to set a break point at current line.
#define ASSERT(x) if (!(x)) __debugbreak();

// Macro used for error handling (should probably be called GLCall, but I'm lazy).
// The backslash '\' will end current line.
// The hash '#' will cast whatever 'x' is into a string.
// '__FILE__' and '__LINE__' are apart of the standard predefined macros for C++.
#define CALL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const; 
};
