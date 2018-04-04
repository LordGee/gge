#pragma once

#define _USE_MATH_DEFINES
#include <corecrt_math_defines.h>

namespace gge
{
	namespace maths
	{
		inline float ToRadians(float degrees) {
			return static_cast<float>(degrees * (M_PI / 180.0f));
		}
	}
}