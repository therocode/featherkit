#pragma once
#include <stdint.h>
#include <array>
#include <random>
#include <algorithm>
#include <fea/util/simplexnoise.hpp>
#include <fea/util/voronoinoise.hpp>
#include <fea/util/whitenoise.hpp>

#ifdef NOISE_ASM
#include <fea/util/asmnoise.hpp>
#endif

namespace fea
{
	const uint32_t globalSeed = 51253;

	using PermutationTable = std::array<uint8_t, 512>;

	class Noise
	{
		public:
			Noise();
			Noise(uint32_t seed);
			void setSeed(uint32_t seed);
			float white2D(float x, float y) const;
			float simplex2D(float x, float y) const;
			float simplexOctave2D(float x, float y, float scaleFactor = 1.0f, uint32_t octaves = 5, float persistence = 0.5f) const;
			float simplex3D(float x, float y, float z) const;
			float simplexOctave3D(float x, float y, float z, float scaleFactor = 1.0f, uint32_t octaves = 5, float persistence = 0.5f) const;
			float voronoi2D(float x, float y) const;
		private:
			WhiteNoise mWhiteNoise;
			VoronoiNoise mVoronoiNoise;
			std::ranlux24_base mRandomEngine;
			PermutationTable mPerm;
	};
}
