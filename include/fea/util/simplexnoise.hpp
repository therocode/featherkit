#pragma once
#include <random>
#include <cstring>
#include <cstdint>

namespace fea
{
	// Raw Simplex noise - a single noise value.
	float raw_noise_2d(float x, float y, const uint8_t* perm);
	float raw_noise_3d(float x, float y, float z, const uint8_t* perm);


	float dot(const int8_t* grad, float x, float y);
	float dot(const int8_t* grad, float x, float y, float z);

	inline int fast_floor(float x);


	// The gradients are the midpoints of the vertices of a cube.
	static const int8_t grad3[12][3] = {
		{1,1,0}, {-1,1,0}, {1,-1,0}, {-1,-1,0},
		{1,0,1}, {-1,0,1}, {1,0,-1}, {-1,0,-1},
		{0,1,1}, {0,-1,1}, {0,1,-1}, {0,-1,-1}
	};
}
