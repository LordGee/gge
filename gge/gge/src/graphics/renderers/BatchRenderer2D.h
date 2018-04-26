#pragma once

#include <glew.h>
#include "Renderer2D.h"
#include "../renderables/Renderable2D.h"
#include "../buffers/IndexBuffer.h"

namespace gge
{
	namespace graphics
	{
#define MAXIMUM_SPRITES			60000
#define VERTEX_SIZE				sizeof(VertexData)
#define SPRITE_SIZE				VERTEX_SIZE * 4
#define BUFFER_SIZE				SPRITE_SIZE * MAXIMUM_SPRITES
#define INDICES_SIZE			MAXIMUM_SPRITES * 6
#define MAXIMUM_TEXTURES		32

#define ATTR_VERTEX_INDEX		0
#define ATTR_UV_INDEX			1
#define ATTR_TEXID_INDEX		2
#define ATTR_COLOUR_INDEX		3

		class BatchRenderer2D : public Renderer2D {
		private:
			GLuint					m_VAO;
			GLuint					m_VBO;
			IndexBuffer*			m_IBO;
			VertexData*				m_Buffer;
			GLsizei					m_IndexCount;
			std::vector<GLuint>		m_TextureSlots;

		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void Begin() override;
			void Submit(const Renderable2D* renderable) override;
			void SubmitText(const std::string& text, const maths::Vector3& position, const Font& font, unsigned int colour) override;
			void End() override;
			void Flush() override;

		private:
			void Init();
		};
	}
}