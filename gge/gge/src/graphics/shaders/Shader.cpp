#include "Shader.h"

namespace gge
{ 
	namespace graphics {
		/* Default constructor, loads in the standard shader */
		Shader::Shader() {
			m_VertexPath = "src/shaders/basic.vert";
			m_FragmentPath = "src/shaders/basic.frag";
			m_ShaderID = LoadInShader();
		}

		/* Define a specific shader for this constructor */
		Shader::Shader(const char* vertexPath, const char* fragmentPath) 
			: m_VertexPath(vertexPath), m_FragmentPath(fragmentPath)
		{
			m_ShaderID = LoadInShader();
		}

		/* Deconstructor removes shader id from the program */
		Shader::~Shader() {
			glDeleteProgram(m_ShaderID);
		}

		/* Sets a single float variable to the given variable name within the shader */
		void Shader::SetUniform1f(const GLchar* name, float value) {
			glUniform1f(GetUniformLocation(name), value);
		}

		/* Sets a single float array variable to the given variable name within the shader */
		void Shader::SetUniform1fv(const GLchar* name, int count, float* value) {
			glUniform1fv(GetUniformLocation(name), count, value);
		}

		/* Sets a single integer variable to the given variable name within the shader */
		void Shader::SetUniform1i(const GLchar* name, int value) {
			glUniform1i(GetUniformLocation(name), value);
		}

		/* Sets a single integer array variable to the given variable name within the shader */
		void Shader::SetUniform1iv(const GLchar* name, int count, int* value) {
			glUniform1iv(GetUniformLocation(name), count, value);
		}

		/* Sets a Vector 2 variable to the given variable name within the shader */
		void Shader::SetUniform2f(const GLchar* name, const maths::Vector2& vec2) {
			glUniform2f(GetUniformLocation(name), vec2.x, vec2.y);
		}

		/* Sets a Vector 3 variable to the given variable name within the shader */
		void Shader::SetUniform3f(const GLchar* name, const maths::Vector3& vec3) {
			glUniform3f(GetUniformLocation(name), vec3.x, vec3.y, vec3.z);
		}

		/* Sets a Vector 4 variable to the given variable name within the shader */
		void Shader::SetUniform4f(const GLchar* name, const maths::Vector4& vec4) {
			glUniform4f(GetUniformLocation(name), vec4.x, vec4.y, vec4.z, vec4.z);
		}

		/* Sets matrix elements variable to the given variable name within the shader */
		void Shader::SetUniformMatrix(const GLchar* name, const maths::Matrix& matrix) {
			glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}

		GLint Shader::GetUniformLocation(const GLchar* name) {
			return glGetUniformLocation(m_ShaderID, name);
		}

		void Shader::Enable() const {
			glUseProgram(m_ShaderID);
		}

		void Shader::Disable() const {
			glUseProgram(0);
		}

GLuint Shader::LoadInShader() {
	/* Creates an empty program object and returns a 
	 * non-zero value by which it can be referenced */
	GLuint program = glCreateProgram();
	/* Creates an empty shader object and returns a 
	 * non-zero value by which it can be referenced */
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	/* Loads in the shader and stored in a string variable */
	std::string vertSourceString = ReadFile(m_VertexPath);
	std::string fragSourceString = ReadFile(m_FragmentPath);
	/* Convert string to a const char* */
	const char* vertexSource = vertSourceString.c_str();
	const char* fragmentSource = fragSourceString.c_str();
	/* Sets the source code in shader to the vertex shader and sets 
	 * the source code to the value the from the vertex file */
	glShaderSource(vertex, 1, &vertexSource, NULL);
	/* Compiles the source code that have been stored in the 
	 * vertex shader object */
	glCompileShader(vertex);
	GLint result;
	/* Gets the vertex shaders, compile status which returns 
	 * GL_TRUE if the last compile operation on shader was 
	 * successful, and GL_FALSE otherwise */
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		HandleShaderError(vertex);
		return 0;
	}
	/* Sets the source code in shader to the fragment shader and sets
	* the source code to the value the from the fragment file */
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	/* Compiles the source code that have been stored in the
	* fragment shader object */
	glCompileShader(fragment);
	result = NULL;
	/* Gets the fragment shaders, compile status which returns
	* GL_TRUE if the last compile operation on shader was
	* successful, and GL_FALSE otherwise */
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		HandleShaderError(fragment);
		return 0;
	}
	/* Attaches the shader to the specified program object */
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	/* Links the program object specified */
	glLinkProgram(program);
	/* Checks to see whether the executables contained in program 
	 * can execute given the current OpenGL state */
	glValidateProgram(program);
	/* Deletes the no longer need shader IDs */
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return program;
}

		void Shader::HandleShaderError(GLuint id) {
			GLint length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(id, length, &length, &error[0]);
			std::cout << "Failed to compile Fragment Shader : " << &error[0] << std::endl;
			glDeleteShader(id);
		}

	}
}
