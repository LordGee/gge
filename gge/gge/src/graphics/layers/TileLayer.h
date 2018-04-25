
#pragma once

#include "Layer.h"
#include "../renderers/BatchRenderer2D.h"

// an example of an object implementation.

class TileLayer : public gge::graphics::Layer {

public:
	TileLayer(gge::graphics::Shader* shader);
	~TileLayer();
};
