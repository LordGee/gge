#pragma once

#include "Layer.h"
#include "../renderers/BatchRenderer2D.h"

namespace gge
{
	namespace graphics
	{
		class TileLayer : public Layer {

		public:
			TileLayer(Shader* shader);
			~TileLayer();
		};
	}
}