#pragma once

#include "Buffer.h"
#include <vector>

namespace gge
{
	namespace graphics
	{
		class VertexArray {
		private:
			GLuint					m_ArrayID;
			std::vector<Buffer*>	m_Buffers;

		public:
			VertexArray();
			~VertexArray();

			void AddBuffer(Buffer* buffer, GLuint index);
			void BindVertexArray() const;
			void UnbindVertexArray() const;
		};
	}
}
