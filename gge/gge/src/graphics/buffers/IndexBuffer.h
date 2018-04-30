#pragma once

#include <glew.h>

namespace gge
{
	namespace graphics
	{
		class IndexBuffer {
		private:
			GLuint			m_BufferID;
			GLuint			m_Count;

		public:
			IndexBuffer(GLuint* data, GLsizei count);
			~IndexBuffer();

			void BindIndexBuffer() const;
			void UnbindIndexBuffer() const;

			GLuint GetCount() const { return m_Count; }
		};
	}
}