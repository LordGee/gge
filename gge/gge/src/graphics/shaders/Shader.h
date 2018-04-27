#pragma once

#include <glew.h>
#include "../../maths/Maths.h"
#include "../../utilities/FileReader.h"
#include <vector>
#include <iostream>


namespace gge
{
	namespace  graphics
	{
		class Shader {
		private:
			GLuint			m_ShaderID;
			const char*		m_VertexPath;
			const char*		m_FragmentPath;

		public:
			Shader();
			Shader(const char* vertexPath, const char* fragmentPath);
			~Shader();

			void SetUniform1f(const GLchar* name, float value);
			void SetUniform1i(const GLchar* name, int value);
			void SetUniform1fv(const GLchar* name, int count, float* value);
			void SetUniform1iv(const GLchar* name, int count, int* value);
			void SetUniform2f(const GLchar* name, const maths::Vector2& vec2);
			void SetUniform3f(const GLchar* name, const maths::Vector3& vec3);
			void SetUniform4f(const GLchar* name, const maths::Vector4& vec4);
			void SetUniformMatrix(const GLchar* name, const maths::Matrix& matrix);

			void Enable() const;
			void Disable() const;

		private:
			GLuint LoadInShader();
			GLint GetUniformLocation(const GLchar* name);
			void HandleShaderError(GLuint id);

		};
	}
}
