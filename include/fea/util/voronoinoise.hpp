#pragma once
#include <stdint.h>

namespace fea
{
	class VoronoiNoise
	{
		public:
			float get2d(float x, float y, const uint8_t* perm) const;
	};
}
