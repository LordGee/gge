#include "BatchRenderer.h"

namespace gge
{
	namespace graphics
	{
		BatchRenderer::BatchRenderer() {
			Init();
		}

		BatchRenderer::~BatchRenderer() {
			delete m_IndexBufferObject;
			glDeleteBuffers(1, &m_VertexBufferObject);
		}

		void BatchRenderer::Init() {
			glGenVertexArrays(1, &m_VertexArrayObject);
			glGenBuffers(1, &m_VertexBufferObject);

			glBindVertexArray(m_VertexArrayObject);
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
			
			glEnableVertexAttribArray(ATTR_VERTEX_INDEX);
			glEnableVertexAttribArray(ATTR_COLOUR_INDEX);
			glEnableVertexAttribArray(ATTR_UV_INDEX);
			glEnableVertexAttribArray(ATTR_TEXID_INDEX);
			
			glVertexAttribPointer(ATTR_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(ATTR_COLOUR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::colour)));
			glVertexAttribPointer(ATTR_UV_INDEX, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::textureCoord)));
			glVertexAttribPointer(ATTR_TEXID_INDEX, 1, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::textureID)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint* indicies = new GLuint[INDICES_SIZE];
			int offset = 0;
			for (int i = 0; i < INDICES_SIZE; i += 6) {
				indicies[i] = offset + 0;
				indicies[i + 1] = offset + 1;
				indicies[i + 2] = offset + 2;
				indicies[i + 3] = offset + 2;
				indicies[i + 4] = offset + 3;
				indicies[i + 5] = offset + 0;
				offset += 4;
			}

			m_IndexBufferObject = new IndexBuffer(indicies, INDICES_SIZE);

			glBindVertexArray(0);
		}

		void BatchRenderer::Begin() {
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
			m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer::Submit(const Renderable* renderable) {
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
					if (m_TextureSlots.size() >= MAXIMUM_TEXTURES) {
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

		void BatchRenderer::SubmitText(const std::string& text, const maths::Vector3& position, const Font& font, unsigned int colour) {
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
				if (m_TextureSlots.size() >= MAXIMUM_TEXTURES) {
					End();
					Flush();
					Begin();
				}
				m_TextureSlots.push_back(font.GetFontID());
				ts = (float)m_TextureSlots.size();
			}

			const maths::Vector2& scale = font.GetScale();
			
			float x = position.x;

			texture_font_t* ftFont = font.GetFont();

			for (int i = 0; i < text.length(); i++) {

				char character = text[i];
				texture_glyph_t* glyph = texture_font_get_glyph(ftFont, character);
				if (glyph != NULL) {
					if (i > 0) {
						float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
						x += kerning / scale.x;
					}
					float x0 = x + glyph->offset_x / scale.x;
					float y0 = position.y + glyph->offset_y / scale.y;
					float x1 = x0 + glyph->width / scale.x;
					float y1 = y0 - glyph->height / scale.y;

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
					x += glyph->advance_x / scale.x;
				}
			}
		}

		void BatchRenderer::End() {
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer::Flush() {

			for (int i = 0; i < m_TextureSlots.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
			}

			glBindVertexArray(m_VertexArrayObject);
			m_IndexBufferObject->BindIndexBuffer();

			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

			m_IndexBufferObject->UnbindIndexBuffer();
			glBindVertexArray(0);

			m_IndexCount = 0;
			m_TextureSlots.clear();
		}
	}
}