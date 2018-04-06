#include "Sprite.h"

namespace gge
{
	namespace graphics
	{
		Sprite::Sprite(float x, float y, float width, float height, const maths::Vector4& colour)
			: Renderable2D(maths::Vector3(x, y, 0), maths::Vector2(width, height), colour) { }

		Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
			: Renderable2D(maths::Vector3(x, y, 0), maths::Vector2(width, height), maths::Vector4(1, 0, 1, 1)) {
			m_Texture = texture;
		}
	}
}