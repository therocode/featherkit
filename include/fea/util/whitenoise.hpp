#pragma once
#include <stdint.h>

namespace fea
{
	class WhiteNoise
	{
		public:
			float get2d(const float x, const float y, const uint8_t* perm) const;
	};
}
