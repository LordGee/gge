#include "Buffer.h"

namespace gge
{
	namespace graphics
	{
		/*
		Buffer::Buffer(GLfloat* data, GLsizei count, GLuint componentCount)
			: m_ComponentCount(componentCount) {
			glGenBuffers(1, &m_BufferID);
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		Buffer::~Buffer() {
			glDeleteBuffers(1, &m_BufferID);
		}

		void Buffer::BindBuffer() const {
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		}

		void Buffer::UnbindBuffer() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		*/
	}
}