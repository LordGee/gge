#include "VertexArray.h"

namespace gge
{
	namespace graphics
	{
		/*
		VertexArray::VertexArray() {
			glGenVertexArrays(1, &m_ArrayID);
		}

		VertexArray::~VertexArray() {
			for (int i = 0; i < m_Buffers.size(); i++) {
				delete m_Buffers[i];
			}
			glDeleteVertexArrays(1, &m_ArrayID);
		}

		void VertexArray::AddBuffer(Buffer* buffer, GLuint index) {
			BindVertexArray();
			buffer->BindBuffer();
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
			buffer->UnbindBuffer();
			UnbindVertexArray();
		}

		void VertexArray::BindVertexArray() const { 
			//glBindVertexArray(m_ArrayID);
		}

		void VertexArray::UnbindVertexArray() const { 
			glBindVertexArray(0);
		}
		*/
	}
}