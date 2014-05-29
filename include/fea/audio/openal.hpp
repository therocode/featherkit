#pragma once
#define AL_ALEXT_PROTOTYPES
#if !defined(__EMSCRIPTEN__)
    #include "al.h"
    #include "alc.h"
#else
	#include <AL/al.h>
	#include <AL/alc.h>
	#if defined(_WIN32)
		#include <AL/efx.h>
	#endif
#endif
