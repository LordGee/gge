#pragma once

#include <glew.h>

namespace gge
{
	namespace graphics
	{
		class Buffer {
		private:
			GLuint			m_BufferID;
			GLuint			m_ComponentCount;

		public:
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
			~Buffer();
			void BindBuffer() const;
			void UnbindBuffer() const;

			GLuint GetComponentCount() const { return m_ComponentCount; }
		};
	}
}