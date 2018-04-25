#include "Sprite.h"

namespace gge
{
	namespace graphics
	{
		Sprite::Sprite(float x, float y, float width, float height, const unsigned int colour)
			: Renderable2D(maths::Vector3(x, y, 0), maths::Vector2(width, height), colour), position(m_Position) { }

		Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
			: Renderable2D(maths::Vector3(x, y, 0), maths::Vector2(width, height), 0xffffffff), position(m_Position)
		{
			m_Texture = texture;
		}
	}
}