#include "BatchRenderer2D.h"

namespace gge
{
	namespace graphics
	{
		BatchRenderer2D::BatchRenderer2D() {
			Init();
		}

		BatchRenderer2D::~BatchRenderer2D() {
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}

		void BatchRenderer2D::Init() {
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
			
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_TID_INDEX);
			glEnableVertexAttribArray(SHADER_COLOUR_INDEX);
			
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::textureCoord)));
			glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::textureID)));
			glVertexAttribPointer(SHADER_COLOUR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::colour)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint* indicies = new GLuint[RENDERER_INDICES_SIZE];
			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
				indicies[i] = offset + 0;
				indicies[i + 1] = offset + 1;
				indicies[i + 2] = offset + 2;
				indicies[i + 3] = offset + 2;
				indicies[i + 4] = offset + 3;
				indicies[i + 5] = offset + 0;
				offset += 4;
			}

			m_IBO = new IndexBuffer(indicies, RENDERER_INDICES_SIZE);

			glBindVertexArray(0);
		}

		void BatchRenderer2D::Begin() {
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::Submit(const Renderable2D* renderable) {
			const maths::Vector3& position = renderable->GetPosition();
			const maths::Vector2& size = renderable->GetSize();
			const unsigned int colour = renderable->GetColour();
			const std::vector<maths::Vector2>& uv = renderable->GetUV();
			const GLuint textureID = renderable->GetTextureID();
			
			float textureSlot = 0.0f;
			if (textureID > 0) {
				bool found = false;
				for (int i = 0; i < m_TextureSlots.size(); i++) {
					if (m_TextureSlots[i] == textureID) {
						textureSlot = (float)(i + 1);
						found = true;
						break;
					}
				}
				if (!found) {
					if (m_TextureSlots.size() >= 32) {
						End();
						Flush();
						Begin();
					}
					m_TextureSlots.push_back(textureID);
					textureSlot = (float)m_TextureSlots.size();
				}
			} 

			m_Buffer->vertex = *m_TransformationBack * position;
			m_Buffer->textureCoord = uv[0];
			m_Buffer->textureID = textureSlot;
			m_Buffer->colour = colour;
			m_Buffer++;

			m_Buffer->vertex = *m_TransformationBack * maths::Vector3(position.x, position.y + size.y, position.z);
			m_Buffer->textureCoord = uv[1];
			m_Buffer->textureID = textureSlot;
			m_Buffer->colour = colour;
			m_Buffer++;

			m_Buffer->vertex = *m_TransformationBack * maths::Vector3(position.x + size.x, position.y + size.y, position.z);
			m_Buffer->textureCoord = uv[2];
			m_Buffer->textureID = textureSlot;
			m_Buffer->colour = colour;
			m_Buffer++;

			m_Buffer->vertex = *m_TransformationBack * maths::Vector3(position.x + size.x, position.y, position.z);
			m_Buffer->textureCoord = uv[3];
			m_Buffer->textureID = textureSlot;
			m_Buffer->colour = colour;
			m_Buffer++;

			m_IndexCount += 6;
		}

		void BatchRenderer2D::End() {
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::Flush() {

			for (int i = 0; i < m_TextureSlots.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
			}

			glBindVertexArray(m_VAO);
			m_IBO->BindIndexBuffer();

			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

			m_IBO->UnbindIndexBuffer();
			glBindVertexArray(0);

			m_IndexCount = 0;
		}
	}
}