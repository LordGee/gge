#pragma once

#include "../../maths/Maths.h"
#include "../shaders/Shader.h"
#include "../renderers/Renderer2D.h"
#include "../textures/Texture.h"

namespace gge
{
	namespace graphics
	{
		struct VertexData {
			maths::Vector3					vertex;
			maths::Vector2					textureCoord;
			float							textureID;
			unsigned int					colour;
		};

		class Renderable2D {
		protected:
			maths::Vector3					m_Position;
			maths::Vector2					m_Size;
			unsigned int					m_Colour;
			std::vector<maths::Vector2>		m_TextureCoord;
			Texture*						m_Texture;

		protected:
			Renderable2D() {
				SetTextureCoordsDefault();
			}

		public:
			Renderable2D(maths::Vector3 position, maths::Vector2 size, unsigned int colour)
				: m_Position(position), m_Size(size), m_Colour(colour) {
				SetTextureCoordsDefault();
			}

			virtual ~Renderable2D() { }

			virtual void Submit(Renderer2D* renderer) const { renderer->Submit(this); }

			void SetColour(unsigned int colour) { m_Colour = colour; }
			void SetColour(maths::Vector4& colour) {
				int r = colour.x * 255.0f;
				int g = colour.y * 255.0f;
				int b = colour.z * 255.0f;
				int a = colour.w * 255.0f;
				m_Colour = a << 24 | b << 16 | g << 8 | r;
			}

			inline const maths::Vector3& GetPosition() const { return m_Position; }
			inline const maths::Vector2& GetSize() const { return m_Size; }
			inline const unsigned int GetColour() const { return m_Colour; }
			inline const std::vector<maths::Vector2>& GetUV() const { return m_TextureCoord; }
			inline const GLuint GetTextureID() const { return m_Texture == nullptr ? 0 : m_Texture->GetTextureID(); }


		private:
			void SetTextureCoordsDefault() {
				m_TextureCoord.push_back(maths::Vector2(0, 0));
				m_TextureCoord.push_back(maths::Vector2(0, 1));
				m_TextureCoord.push_back(maths::Vector2(1, 1));
				m_TextureCoord.push_back(maths::Vector2(1, 0));
			}
		};
	}
}
