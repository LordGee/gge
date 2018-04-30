#pragma once

#include "Renderable.h"

namespace gge
{
	namespace graphics
	{
		class Sprite : public Renderable {
		public:
			maths::Vector3& position;
		public:
			Sprite(float x, float y, float width, float height, unsigned int colour);
			Sprite(float x, float y, float width, float height, Texture* texture);
		};
	}
}