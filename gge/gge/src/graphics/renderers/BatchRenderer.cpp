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
			/* Returns vertex array object names */
			glGenVertexArrays(1, &m_VertexArrayObject);
			/* Returns buffer object names */
			glGenBuffers(1, &m_VertexBufferObject);
			/* Binds the vertex array object with name */
			glBindVertexArray(m_VertexArrayObject);
			/* Binds a buffer object to the specified buffer
			 * binding point */
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
			/* Create a new data store for a buffer object */
			glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL,
				GL_DYNAMIC_DRAW);
			/* Enable the generic vertex attribute array specified
			 * by index */
			glEnableVertexAttribArray(ATTR_VERTEX_INDEX);
			glEnableVertexAttribArray(ATTR_COLOUR_INDEX);
			glEnableVertexAttribArray(ATTR_UV_INDEX);
			glEnableVertexAttribArray(ATTR_TEXID_INDEX);
			/* Specify the location and data format of the
			 * array of generic vertex attributes at index to use
			 * when rendering */
			glVertexAttribPointer(ATTR_VERTEX_INDEX, 3, GL_FLOAT,
				GL_FALSE, VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(ATTR_COLOUR_INDEX, 4, GL_UNSIGNED_BYTE,
				GL_TRUE, VERTEX_SIZE,
				(const GLvoid*)(offsetof(VertexData, VertexData::colour)));
			glVertexAttribPointer(ATTR_UV_INDEX, 2, GL_FLOAT,
				GL_FALSE, VERTEX_SIZE,
				(const GLvoid*)(offsetof(VertexData, VertexData::textureCoord)));
			glVertexAttribPointer(ATTR_TEXID_INDEX, 1, GL_FLOAT,
				GL_FALSE, VERTEX_SIZE,
				(const GLvoid*)(offsetof(VertexData, VertexData::textureID)));
			/* Unbinds a buffer object */
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			/* Generates the indicies values that will draw
			 * two triagles to make a square */
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
			/* Create instance of the IndexBuffer pasiing over the indicies
			 * data and size */
			m_IndexBufferObject = new IndexBuffer(indicies, INDICES_SIZE);
			/* Unbinds the vertex array object */
			glBindVertexArray(0);
		}

		void BatchRenderer::Begin() {
			/* Binds a buffer object to the specified buffer binding point */
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
			/* Map the entire data store of a specified buffer object */
			m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer::Submit(const Renderable* renderable) {
			// Set values based on renderable object
			const maths::Vector3& position = renderable->GetPosition();
			const maths::Vector2& size = renderable->GetSize();
			const unsigned int colour = renderable->GetColour();
			const std::vector<maths::Vector2>& uv = renderable->GetUV();
			const GLuint textureID = renderable->GetTextureID();

			// Identify Texture ID
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
				// if not found add to array
				if (!found) {
					// if max textures, then end, flush and begin
					if (m_TextureSlots.size() >= MAXIMUM_TEXTURES) {
						End();
						Flush();
						Begin();
					}
					
					m_TextureSlots.push_back(textureID);
					textureSlot = (float)m_TextureSlots.size();
				}
			} 
			// Set Vertex Data values at each four points
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
			/* Initilase texture slot value to 0.0 */
			float ts = 0.0f;
			/* Initialise found value to false */
			bool found = false;
			/* Iterate through texture slots */
			for (int i = 0; i < m_TextureSlots.size(); i++) {
				if (m_TextureSlots[i] == font.GetFontID()) {
					/* if the texture slot value is the same as the texture 
					 * ID then the texture has been found*/
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}
			if (!found) {
				/* If the texture ID has not been found in the current array */
				if (m_TextureSlots.size() >= MAXIMUM_TEXTURES) {
					/* If the amount of textures in the array exceed the maximum 
					 * amount of texture, the whats already in there gets commited 
					 * and emptied before any textures get added */
					End();
					Flush();
					Begin();
				}
				/* Add new font id to the texture slot array */
				m_TextureSlots.push_back(font.GetFontID());
				/* Set the texture slot value as the newly create index value */
				ts = (float)m_TextureSlots.size();
			}
			/* Define the scale of the window */
			const maths::Vector2& scale = font.GetScale();
			/* Set starting x position */
			float x = position.x;
			/* Get the font required */
			ftgl::texture_font_t* ftFont = font.GetFont();
			/* Iterate through each character */
			for (int i = 0; i < text.length(); i++) {
				/* Get one character ata time */
				char character = text[i];
				/* Get the correct character from the font glyphs */
				ftgl::texture_glyph_t* glyph = texture_font_get_glyph(ftFont, character);
				if (glyph != NULL) {
					/* If the character is valid */
					if (i > 0) {
						/* If the character being drawn is not the first character then 
						 * the x position needs to move across for the next character to 
						 * have appropriate spacing, without this all the character will 
						 * be drawn on top of each other */
						float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
						x += kerning / scale.x;
					}
					/* Configure the x y position that the glyph will be drawn to ensure each character is in line */
					float x0 = x + glyph->offset_x / scale.x;
					float y0 = position.y + glyph->offset_y / scale.y;
					float x1 = x0 + glyph->width / scale.x;
					float y1 = y0 - glyph->height / scale.y;
					/* Configure the x y position of the texture */
					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;
					// Set Vertex Data values at each four points
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
					/* Advance the x position ready for the next iteration */
					x += glyph->advance_x / scale.x;
				}
			}
		}

		void BatchRenderer::End() {
			/* Unmaps the buffer array */
			glUnmapBuffer(GL_ARRAY_BUFFER);
			/* Unbinds the buffer array */
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer::Flush() {
			/* Binds and Activates all Textures */
			for (int i = 0; i < m_TextureSlots.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
			}
			/* Binds the Vertex array object */
			glBindVertexArray(m_VertexArrayObject);
			/* Bind the index buffer */
			m_IndexBufferObject->BindIndexBuffer();
			/* Draw all elemets */
			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);
			/* Unbind Index Buffer */
			m_IndexBufferObject->UnbindIndexBuffer();
			/* Unbind Vertex Array */
			glBindVertexArray(0);
			/* Reset index count to 0 ready for next frame */
			m_IndexCount = 0;
			/* Clear all texture slots */
			m_TextureSlots.clear();
		}
	}
}