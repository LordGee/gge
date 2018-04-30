#include "IndexBuffer.h"

namespace gge
{
	namespace graphics
	{
		IndexBuffer::IndexBuffer(GLuint* data, GLsizei count)
			: m_Count(count) {
			glGenBuffers(1, &m_BufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		IndexBuffer::~IndexBuffer() {
			glDeleteBuffers(1, &m_BufferID);
		}

		void IndexBuffer::BindIndexBuffer() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		}

		void IndexBuffer::UnbindIndexBuffer() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}