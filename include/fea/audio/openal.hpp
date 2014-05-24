#pragma once
#define AL_ALEXT_PROTOTYPES
#if !defined(__EMSCRIPTEN__)
#include "al.h"
#include "alc.h"
#include "efx.h"
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif
