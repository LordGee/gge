#pragma once

#include "../../maths/Maths.h"
#include "../Shader.h"
#include "Renderer2D.h"

namespace gge
{
	namespace graphics
	{
		struct VertexData {
			maths::Vector3			vertex;
			unsigned int			colour;
		};

		class Renderable2D {
		protected:
			maths::Vector3			m_Position;
			maths::Vector2			m_Size;
			maths::Vector4			m_Colour;

		protected:
			Renderable2D() { }

		public:
			Renderable2D(maths::Vector3 position, maths::Vector2 size, maths::Vector4 colour)
				: m_Position(position), m_Size(size), m_Colour(colour) { }

			virtual ~Renderable2D() { }

			virtual void Submit(Renderer2D* renderer) const { renderer->Submit(this); }

			inline const maths::Vector3& GetPosition() const { return m_Position; }
			inline const maths::Vector2& GetSize() const { return m_Size; }
			inline const maths::Vector4& GetColour() const { return m_Colour; }
		};
	}
}
