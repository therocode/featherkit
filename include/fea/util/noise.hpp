#pragma once
#include <stdint.h>
#include <array>
#include <random>
#include <algorithm>
#include <fea/util/simplexnoise.hpp>
#include <fea/util/voronoinoise.hpp>
#include <fea/util/whitenoise.hpp>

#ifdef NOISE_ASM
#include <fea/util/asmchecksse41.hpp>
#include <fea/util/asmnoise.hpp>
#endif

namespace fea
{
	class FEA_API Noise
	{
        using PermutationTable = std::array<uint8_t, 512>;
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
			bool asmCompatible;
	};

    /** @addtogroup Util
     *@{
     *  @class Noise
     *@}
     ***
     *  @class Noise
     *  @brief Class capable of producing various kinds of noise.
     *
     *  The following noise functions are supported:
     *  - 2D white noise.
     *  - 2D/3D simplex noise.
     *  - 2D/3D octaved simplex noise.
     *  - 2D Voronoi noise.
     *
     *  These noise fields can be used for example for landscape generation or texture generation.
     *
     *  Variations of the patterns can be achieved by setting different seed values. The same seed will always yield the same pattern on the same machine, but not necessarily across different machines.
     *
     *  If enabled in the compilation, the noise functions will be optimized using assembly.
     ***
     *  @fn Noise::Noise()
     *  @brief Construct a Noise.
	 ***
     *  @fn Noise::Noise(uint32_t seed)
     *  @brief Construct a Noise with a specific seed.
	 ***
     *  @fn void Noise::setSeed(uint32_t seed)
     *  @brief Set the seed of the Noise instance.
     *
     *  Every seed creates a unique noise pattern, so setting the seed is a way of "randomizing" the output given. Note that whilst every seed will give the same output on any given computer, it is not guaranteed to be consistent through different computers.
     *  @param seed Seed value.
	 ***
     *  @fn float Noise::white2D(float x, float y) const
     *  @brief Generate a single coordinate of 2-dimensional white noise.
     *
     *  White noise is comparable to the noise seen on old TVs when receiving no signal.
     *  @param x X coordinate to generate.
     *  @param y Y coordinate to generate.
	 ***
     *  @fn float Noise::simplex2D(float x, float y) const
     *  @brief Generate a single coordinate of 2-dimensional simplex noise.
     *
     *  Simplex noise, or "improved perlin noise" as it is also known by, is a smoother kind of coherent noise. It is often layered together to create landscape heightmaps and other such things. The simplexOctave2D function is a convenience function for layering simplex noise in such a manner.
     *  @param x X coordinate to generate.
     *  @param y Y coordinate to generate.
	 ***
     *  @fn float Noise::simplexOctave2D(float x, float y, float scaleFactor = 1.0f, uint32_t octaves = 5, float persistence = 0.5f) const
     *  @brief Generate a single coordinate of layered 2-dimensional simplex noise.
     *
     *  This layers several "octaves" of simplex noise together to produce a more interesting result. An octave is a scaled layer of noise. Note that as the amount of octaves increases, so does the computational time.
     *
     *  Assert/undefined behaviour when zero or less is given as the octave value.
     *  @param x X coordinate to generate.
     *  @param y Y coordinate to generate.
     *  @param scaleFactor The size of the output noise.
     *  @param octaves Amount of octaves. More octaves gives more detail, but is heavier to compute.
     *  @param persistence Controls the roughness of the noise.
	 ***
     *  @fn float Noise::simplex3D(float x, float y, float z) const
     *  @brief Generate a single coordinate of 3-dimensional simplex noise.
     *
     *  Simplex noise, or "improved perlin noise" as it is also known by, is a smoother kind of coherent noise. It is often layered together to create landscape heightmaps and other such things. The simplexOctave3D function is a convenience function for layering simplex noise in such a manner.
     *  @param x X coordinate to generate.
     *  @param y Y coordinate to generate.
     *  @param z Z coordinate to generate.
	 ***
     *  @fn float Noise::simplexOctave3D(float x, float y, float z, float scaleFactor = 1.0f, uint32_t octaves = 5, float persistence = 0.5f) const
     *  @brief Generate a single coordinate of layered 3-dimensional simplex noise.
     *
     *  This layers several "octaves" of simplex noise together to produce a more interesting result. An octave is a scaled layer of noise. Note that as the amount of octaves increases, so does the computational time.
     *
     *  Assert/undefined behaviour when zero or less is given as the octave value.
     *  @param x X coordinate to generate.
     *  @param y Y coordinate to generate.
     *  @param z Z coordinate to generate.
     *  @param scaleFactor The size of the output noise.
     *  @param octaves Amount of octaves. More octaves gives more detail, but is heavier to compute.
     *  @param persistence Controls the roughness of the noise.
	 ***
     *  @fn float Noise::voronoi2D(float x, float y) const
     *  @brief Generate a single coordinate of 2-dimensional voronoi noise.
     *
     *  Voronoi noise is also known as Worley noise or cell noise. It produces a mosaic-ish pattern with distinct regions.
     *
     *  @param x X coordinate to generate.
     *  @param y Y coordinate to generate.
     ***/
}
