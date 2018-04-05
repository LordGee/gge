#pragma once

#include "Renderable2D.h"

namespace gge
{
	namespace graphics
	{
		class Sprite : public Renderable2D {
		public:
			Sprite(float x, float y, float width, float height, const maths::Vector4& colour);
		};
	}
}