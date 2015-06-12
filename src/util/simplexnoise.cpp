#include <fea/util/simplexnoise.hpp>
#include <cmath>

namespace fea
{
	float raw_noise_2d(float x, float y, const uint8_t* perm)
	{
		const float F2 = 0.5f * (std::sqrt(3.0f) - 1.0f);
		float s = (x + y) * F2;

		float i = fast_floor(x + s);
		float j = fast_floor(y + s);

		const float G2 = (3.0f - std::sqrt(3.0f)) / 6.0f;
		float t = (i + j) * G2;

		float x0 = x - (i - t);
		float y0 = y - (j - t);

		uint8_t i1 = 0;
		uint8_t j1 = 1;
		if(x0 > y0)
		{
			i1 = 1;
			j1 = 0;
		}

		float x1 = x0 - i1 + G2;
		float y1 = y0 - j1 + G2;
		float x2 = x0 - 1.0f + 2.0f * G2;
		float y2 = y0 - 1.0f + 2.0f * G2;

		uint8_t ii = uint8_t(i);
		uint8_t jj = uint8_t(j);

		uint8_t gi0 = perm[ii + perm[jj     ]     ] % 12;
		uint8_t gi1 = perm[ii + perm[jj + j1] + i1] % 12;
		uint8_t gi2 = perm[ii + perm[jj + 1 ] + 1 ] % 12;

		float t0 = 0.5f - x0 * x0 - y0 * y0;
		float t1 = 0.5f - x1 * x1 - y1 * y1;
		float t2 = 0.5f - x2 * x2 - y2 * y2;

		float n0 = (t0 < 0) ? 0.0f : t0*t0*t0*t0 * dot(grad3[gi0], x0, y0);
		float n1 = (t1 < 0) ? 0.0f : t1*t1*t1*t1 * dot(grad3[gi1], x1, y1);
		float n2 = (t2 < 0) ? 0.0f : t2*t2*t2*t2 * dot(grad3[gi2], x2, y2);

		return 70.0f * (n0 + n1 + n2);
	}


	float raw_noise_3d(float x, float y, float z, const uint8_t* perm)
	{
		constexpr float F3 = 1.0f / 3.0f;
		float s = (x + y + z) * F3;

		float i = fast_floor(x + s);
		float j = fast_floor(y + s);
		float k = fast_floor(z + s);

		constexpr float G3 = 1.0f / 6.0f;
		float t = (i + j + k) * G3;

		float x0 = x - (i - t);
		float y0 = y - (j - t);
		float z0 = z - (k - t);

		uint8_t i1 = 0, j1 = 1, k1 = 0;
		uint8_t i2 = 1, j2 = 1, k2 = 0;
		if(x0 >= y0)
		{
			if(y0 >= z0)
			{
				i1 = 1; j1 = 0; k1 = 0;
				i2 = 1; j2 = 1; k2 = 0;
			}
			else if(x0 >= z0)
			{
				i1 = 1; j1 = 0; k1 = 0;
				i2 = 1; j2 = 0; k2 = 1;
			}
			else
			{
				i1 = 0; j1 = 0; k1 = 1;
				i2 = 1; j2 = 0; k2 = 1;
			}
		}
		else
		{
			if(y0 < z0)
			{
				i1 = 0; j1 = 0; k1 = 1;
				i2 = 0; j2 = 1; k2 = 1;
			}
			else if(x0 < z0)
			{
				i1 = 0; j1 = 1; k1 = 0;
				i2 = 0; j2 = 1; k2 = 1;
			}
		}

		float x1 = x0 - i1   + G3;
		float y1 = y0 - j1   + G3;
		float z1 = z0 - k1   + G3;
		float x2 = x0 - i2   + G3 * 2.0f;
		float y2 = y0 - j2   + G3 * 2.0f;
		float z2 = z0 - k2   + G3 * 2.0f;
		float x3 = x0 - 1.0f + G3 * 3.0f;
		float y3 = y0 - 1.0f + G3 * 3.0f;
		float z3 = z0 - 1.0f + G3 * 3.0f;

		uint8_t ii = uint8_t(i);
		uint8_t jj = uint8_t(j);
		uint8_t kk = uint8_t(k);

		uint8_t gi0 = perm[ii + perm[jj + perm[kk     ]     ]     ] % 12;
		uint8_t gi1 = perm[ii + perm[jj + perm[kk + k1] + j1] + i1] % 12;
		uint8_t gi2 = perm[ii + perm[jj + perm[kk + k2] + j2] + i2] % 12;
		uint8_t gi3 = perm[ii + perm[jj + perm[kk + 1 ] + 1 ] + 1 ] % 12;

		float t0 = 0.5f - x0 * x0 - y0 * y0 - z0 * z0;
		float t1 = 0.5f - x1 * x1 - y1 * y1 - z1 * z1;
		float t2 = 0.5f - x2 * x2 - y2 * y2 - z2 * z2;
		float t3 = 0.5f - x3 * x3 - y3 * y3 - z3 * z3;

		float n0 = (t0 < 0) ? 0.0f : t0*t0*t0*t0 * dot(grad3[gi0], x0, y0, z0);
		float n1 = (t1 < 0) ? 0.0f : t1*t1*t1*t1 * dot(grad3[gi1], x1, y1, z1);
		float n2 = (t2 < 0) ? 0.0f : t2*t2*t2*t2 * dot(grad3[gi2], x2, y2, z2);
		float n3 = (t3 < 0) ? 0.0f : t3*t3*t3*t3 * dot(grad3[gi3], x3, y3, z3);

		return 32.0f * (n0 + n1 + n2 + n3);
	}


	float dot(const int8_t* grad, float x, float y)
	{
		return grad[0] * x + grad[1] * y;
	}


	float dot(const int8_t* grad, float x, float y, float z)
	{
		return grad[0] * x + grad[1] * y + grad[2] * z;
	}

	inline int fast_floor(float x){return ((x>=0)?((int)x):((x==(int)x)?(int)x:((int)x)-1));}
}
