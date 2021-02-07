#pragma once

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

class Application {
public:
	Application();
	void init();
	void render();
	inline unsigned int getShader() { return mShader; }

private:
	struct ShaderProgramSource {
		std::string VertexSource;
		std::string FragmentSource;

		enum class ShaderType {
			NONE = -1,
			VERTEX = 0,
			FRAGMENT = 1
		};
	};
	
	static ShaderProgramSource ParseShader(const std::string& filepath);
	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	static void GLClearError();
	static bool GLLogCall(const char* function, const char* file, int line);
	unsigned int mVAO;
	unsigned int mShader;
	unsigned int mVBO;
	unsigned int mIBO;
	float mIncrement;
	int mUniformLoc; // Make this into an array if more locations are needed

};