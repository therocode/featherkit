namespace fea
{
	extern "C" float asm_raw_noise_2d(const float x, const float y, const uint8_t* permpointer);
	extern "C" float asm_raw_noise_3d(const float x, const float y, const float z, const uint8_t* permpointer);

	extern "C" float asm_VoronoiNoise_2d(const float x, const float y, const uint8_t* permpointer);

	extern "C" float asm_WhiteNoise_2d(const float x, const float y, const uint8_t* permpointer);
}
