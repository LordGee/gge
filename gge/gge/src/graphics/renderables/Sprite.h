#pragma once

#include "Renderable2D.h"

namespace gge
{
	namespace graphics
	{
		class Sprite : public Renderable2D {
		public:
			maths::Vector3& position;
		public:
			Sprite(float x, float y, float width, float height, unsigned int colour);
			Sprite(float x, float y, float width, float height, Texture* texture);
		};
	}
}