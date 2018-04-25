

#include "TileLayer.h"

// an example of an object implementation.

TileLayer::TileLayer(gge::graphics::Shader* shader)
	: gge::graphics::Layer(new gge::graphics::BatchRenderer2D(), shader, gge::maths::Matrix::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f)) { }

TileLayer::~TileLayer() { }

