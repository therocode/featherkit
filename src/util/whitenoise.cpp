#include <fea/util/whitenoise.hpp>
#include <cmath>

namespace fea
{
	float WhiteNoise::get2d(const float x, const float y, const uint8_t* perm) const
	{
        float floorX = std::floor(x);
        float floorY = std::floor(y);

		uint8_t i = int32_t(floorX);
		uint8_t j = int32_t(floorY);

		uint8_t res = perm[i + perm[j]];

		return (float) res / 255.0f;
	}
}
