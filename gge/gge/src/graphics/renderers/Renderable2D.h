#pragma once

#include "../../maths/Maths.h"
#include "../Shader.h"
#include "Renderer2D.h"
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
			maths::Vector4					m_Colour;
			std::vector<maths::Vector2>		m_TextureCoord;
			Texture*						m_Texture;

		protected:
			Renderable2D() {
				SetTextureCoordsDefault();
			}

		public:
			Renderable2D(maths::Vector3 position, maths::Vector2 size, maths::Vector4 colour)
				: m_Position(position), m_Size(size), m_Colour(colour) {
				SetTextureCoordsDefault();
			}

			virtual ~Renderable2D() { }

			virtual void Submit(Renderer2D* renderer) const { renderer->Submit(this); }

			inline const maths::Vector3& GetPosition() const { return m_Position; }
			inline const maths::Vector2& GetSize() const { return m_Size; }
			inline const maths::Vector4& GetColour() const { return m_Colour; }
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
