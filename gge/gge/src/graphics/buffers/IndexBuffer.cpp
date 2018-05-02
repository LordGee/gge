#include "IndexBuffer.h"

namespace gge
{
	namespace graphics
	{
		IndexBuffer::IndexBuffer(GLuint* data, GLsizei count)
			: m_Count(count) {
			/* Generate and empty buffer object */
			glGenBuffers(1, &m_BufferID);
			/* Bind the buffer ready for use */
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
			/* Apply vertex data to the buffer element */
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
			/* Unbind buffer ready for next iteration */
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		IndexBuffer::~IndexBuffer() {
			/* Delete buffer */
			glDeleteBuffers(1, &m_BufferID);
		}

		void IndexBuffer::BindIndexBuffer() const {
			/* Bind index buffer */
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		}

		void IndexBuffer::UnbindIndexBuffer() const {
			/* Unbind index buffer */
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}