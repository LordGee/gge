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

		void BatchRenderer2D::SubmitText(const std::string& text, const maths::Vector3& position, const Font& font, unsigned int colour) {
			using namespace  ftgl;

			float ts = 0.0f;
			bool found = false;
			for (int i = 0; i < m_TextureSlots.size(); i++) {
				if (m_TextureSlots[i] == font.GetFontID()) {
					ts = (float)(i + 1);
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
				m_TextureSlots.push_back(font.GetFontID());
				ts = (float)m_TextureSlots.size();
			}

			float scaleX = 1920.0f / 32.0f;
			float scaleY = 1080.0f / 18.0f;

			float x = position.x;

			texture_font_t* ftFont = font.GetFont();

			for (int i = 0; i < text.length(); i++) {

				char character = text[i];
				texture_glyph_t* glyph = texture_font_get_glyph(ftFont, character);
				if (glyph != NULL) {
					if (i > 0) {
						float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
						x += kerning / scaleX;
					}
					float x0 = x + glyph->offset_x / scaleX;
					float y0 = position.y + glyph->offset_y / scaleY;
					float x1 = x0 + glyph->width / scaleX;
					float y1 = y0 - glyph->height / scaleY;

					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;

					m_Buffer->vertex = *m_TransformationBack * maths::Vector3(x0, y0, 0);
					m_Buffer->textureCoord = maths::Vector2(u0, v0);
					m_Buffer->textureID = ts;
					m_Buffer->colour = colour;
					m_Buffer++;

					m_Buffer->vertex = *m_TransformationBack * maths::Vector3(x0, y1, 0);
					m_Buffer->textureCoord = maths::Vector2(u0, v1);
					m_Buffer->textureID = ts;
					m_Buffer->colour = colour;
					m_Buffer++;

					m_Buffer->vertex = *m_TransformationBack * maths::Vector3(x1, y1, 0);
					m_Buffer->textureCoord = maths::Vector2(u1, v1);
					m_Buffer->textureID = ts;
					m_Buffer->colour = colour;
					m_Buffer++;

					m_Buffer->vertex = *m_TransformationBack * maths::Vector3(x1, y0, 0);
					m_Buffer->textureCoord = maths::Vector2(u1, v0);
					m_Buffer->textureID = ts;
					m_Buffer->colour = colour;
					m_Buffer++;

					m_IndexCount += 6;
					x += glyph->advance_x / scaleX;
				}
			}
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