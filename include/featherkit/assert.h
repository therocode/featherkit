#pragma once
#include <iostream>

#ifndef NDEBUG
#   define FEA_ASSERT(condition, message) \
    do\
    { \
        if(!(condition))\
        { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
            << " line " << __LINE__ << ": " << message << std::endl; \
            std::exit(EXIT_FAILURE); \
        } \
    } while (false)
#else
#   define FEA_ASSERT(condition, message) do { } while (false)
#endif
