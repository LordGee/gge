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

			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertSourceString = ReadFile(m_VertexPath);
			std::string fragSourceString = ReadFile(m_FragmentPath);

			const char* vertexSource = vertSourceString.c_str();
			const char* fragmentSource = fragSourceString.c_str();

			glShaderSource(vertex, 1, &vertexSource, NULL);
			glCompileShader(vertex);
			GLint result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				HandleShaderError(vertex);
				return 0;
			}

			glShaderSource(fragment, 1, &fragmentSource, NULL);
			glCompileShader(fragment);
			result = NULL;
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				HandleShaderError(fragment);
				return 0;
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glLinkProgram(program);
			glValidateProgram(program);

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
