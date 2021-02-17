#pragma once

class Application {
public:
	Application();
	~Application();
	void init();
	void render();
	inline unsigned int getShader() { return m_Shader; }

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
	unsigned int m_Shader;
	class VertexArray* va;
	class VertexBuffer* vb;
	class IndexBuffer* ib;
	float m_Increment;
	int m_UniformLoc; // Make this into an array if more locations are needed

};