#pragma once
#include <iostream>
#include <csignal>

#ifndef SIGTRAP
#define SIGTRAP 5
#endif

#ifndef EMSCRIPTEN
#define FEA_HALT raise(SIGTRAP)
#else
#define FEA_HALT exit(1)
#endif

#ifndef NDEBUG
#   define FEA_ASSERT(condition, message) \
    do\
    { \
        if(!(condition))\
        { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
            << " function " << __func__ << " line " << __LINE__ << ": " << message << std::endl; \
            FEA_HALT; \
        } \
    } while (false)
#else
#   define FEA_ASSERT(condition, message) do { } while (false)
#endif


//raise(SIGTRAP);
//std::exit(EXIT_FAILURE);
