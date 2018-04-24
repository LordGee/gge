#pragma once

#include <glew.h>
#include "Renderer2D.h"
#include "../renderables/Renderable2D.h"
#include "../buffers/IndexBuffer.h"

namespace gge
{
	namespace graphics
	{
#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES	32

#define SHADER_VERTEX_INDEX		0
#define SHADER_UV_INDEX			1
#define SHADER_TID_INDEX		2
#define SHADER_COLOUR_INDEX		3

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