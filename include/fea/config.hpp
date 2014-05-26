#pragma once

#if defined(_WIN32)
    #define FEA_API_EXPORT __declspec(dllexport)
    #define FEA_API_IMPORT __declspec(dllimport)
#else
    #define FEA_API_EXPORT
    #define FEA_API_IMPORT
#endif

#if defined(FEA_EXPORT)
    #define FEA_API FEA_API_EXPORT
#else
    #define FEA_API FEA_API_IMPORT
#endif
