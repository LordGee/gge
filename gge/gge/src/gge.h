#pragma once

#include "graphics/windows/Window.h"
#include "maths/Maths.h"
#include "graphics/shaders/Shader.h"

#include "graphics/layers/TileLayer.h"
#include "graphics/renderers/Sprite.h"
#include "graphics/layers/Group.h"

#define GGE_SHADER_BASIC_VERT "src/shaders/basic.vert"
#define GGE_SHADER_BASIC_FRAG "src/shaders/basic.frag"
#define GGE_SHADER_BASIC_FRAG_LIGHT "src/shaders/light.frag"
#define GGE_SHADER_LIGHT_POS "light_pos"
#define GGE_SHADER_TEXTURES "textures"

static gge::maths::Vector2 MouseWorldPosition(double x, double y, float w, float h) {
	return gge::maths::Vector2(static_cast<float>(x * 32.0f / w - 16.0f), static_cast<float>(9.0f - y * 18.0f / h));
}