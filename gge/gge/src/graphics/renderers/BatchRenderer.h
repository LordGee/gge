#pragma once

#include <glew.h>
#include "Renderer.h"
#include "../renderables/Renderable.h"
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

		class BatchRenderer : public Renderer {
		private:
			GLuint					m_VertexArrayObject;
			GLuint					m_VertexBufferObject;
			IndexBuffer*			m_IndexBufferObject;
			VertexData*				m_Buffer;
			GLsizei					m_IndexCount;
			std::vector<GLuint>		m_TextureSlots;

		public:
			BatchRenderer();
			~BatchRenderer();

			void Begin() override;
			void Submit(const Renderable* renderable) override;
			void SubmitText(const std::string& text, const maths::Vector3& position, const Font& font, unsigned int colour) override;
			void End() override;
			void Flush() override;

		private:
			void Init();
		};
	}
}