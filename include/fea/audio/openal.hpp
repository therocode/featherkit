#pragma once
#define AL_ALEXT_PROTOTYPES
#if !defined(__EMSCRIPTEN__) && !defined(_WIN32)
	#include "al.h"
	#include "alc.h"
	#include "efx.h"
#else
	#include <AL/al.h>
	#include <AL/alc.h>
	#if defined(_WIN32)
		#include <AL/efx.h>
	#endif
#endif
