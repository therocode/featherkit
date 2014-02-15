#pragma once
#include <iostream>
#include <csignal>

#ifndef SIGTRAP
#define SIGTRAP 5
#endif

#ifndef NDEBUG
#   define FEA_ASSERT(condition, message) \
    do\
    { \
        if(!(condition))\
        { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
            << " line " << __LINE__ << ": " << message << std::endl; \
            raise(SIGTRAP); \
        } \
    } while (false)
#else
#   define FEA_ASSERT(condition, message) do { } while (false)
#endif


//raise(SIGTRAP);
//std::exit(EXIT_FAILURE); \
