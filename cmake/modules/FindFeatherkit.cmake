set( FEATHERKIT_FOUND false)

find_path(
    FEATHERKIT_INCLUDE_DIR
    fea/config.hpp
    PATH_SUFFIXES
    include
    PATHS
    ${FEATHERKIT_ROOT}
    ${FEATHERKITDIR}
    $ENV{FEATHERKITDIR}
    $ENV{FEATHERKIT_ROOT}
    /usr
    /usr/local
    ~/Library/Frameworks
    /Library/Frameworks
    /sw
    /opt/local
    /opt/csw
    /opt
    "C:/Program Files (x86)"
    "C:/Program Files (x86)/featherkit"
)

set(FIND_Featherkit_LIB_PATHS
    ${FEATHERKIT_ROOT}
    ${FEATHERKITDIR}
    $ENV{FEATHERKITDIR}
    $ENV{FEATHERKIT_ROOT}
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt
    "C:/Program Files (x86)"
    "C:/Program Files (x86)/featherkit"
)

#list(FIND Featherkit_FIND_COMPONENTS "rendering" Featherkit_NEEDS_GLM)

#if(Featherkit_NEEDS_GLM EQUAL -1)
#    message("i don't need glm!")
#else()
#    message("i need glm!")
#endif()

set(FEATHERKIT_FOUND)
set(FEATHERKIT_LIBRARY)
set(FEATHERKIT_INCLUDE_DIR)

set(FEA_PRESERVE_LIBS false CACHE "" INTERNAL)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(FEA_LIBRARY_SUFFIX "-d")
    set(FEA_LIBRARY_ANTISUFFIX "")
    set(BUILD_TYPE "debug")
    set(ANTI_BUILD_TYPE "release")
else()
    set(FEA_LIBRARY_SUFFIX "")
    set(FEA_LIBRARY_ANTISUFFIX "-d")
    set(BUILD_TYPE "release")
    set(ANTI_BUILD_TYPE "debug")
endif()

if(NOT (${FEA_LAST_MODE} MATCHES ${BUILD_TYPE}))
    unset(FEA_LAST_MODE CACHE)
    set(FEA_LAST_MODE ${BUILD_TYPE} CACHE "" INTERNAL)
    set(FEA_RESET_LIBS true)
else()
    set(FEA_RESET_LIBS false)
endif()

foreach(FIND_Featherkit_COMPONENT ${Featherkit_FIND_COMPONENTS})
    string(TOLOWER ${FIND_Featherkit_COMPONENT} FIND_Featherkit_COMPONENT)
    set(FEATHERKIT_CURRENT_COMPONENT ${FIND_Featherkit_COMPONENT}${FEA_LIBRARY_SUFFIX})

    set(FIND_Featherkit_COMPONENT_NAME fea-${FEATHERKIT_CURRENT_COMPONENT})

    if(${FEA_RESET_LIBS})
        unset(Featherkit_${FIND_Featherkit_COMPONENT}_LIBRARY CACHE)
    endif()

    find_library(Featherkit_${FIND_Featherkit_COMPONENT}_LIBRARY
        NAMES ${FIND_Featherkit_COMPONENT_NAME}
        PATH_SUFFIXES lib64 lib
        PATHS ${FIND_Featherkit_LIB_PATHS})

    #second pass with anti suffix
    if(NOT Featherkit_${FIND_Featherkit_COMPONENT}_LIBRARY)
        #let the user know
        if(NOT Featherkit_FIND_QUIETLY)
            message(WARNING "Failed to find ${BUILD_TYPE} version of fea-${FIND_Featherkit_COMPONENT}. Will try to find ${ANTI_BUILD_TYPE} version instead.")
        endif()

        set(FEATHERKIT_CURRENT_COMPONENT ${FIND_Featherkit_COMPONENT}${FEA_LIBRARY_ANTISUFFIX})

        set(FIND_Featherkit_COMPONENT_NAME fea-${FEATHERKIT_CURRENT_COMPONENT})
        
        if(${FEA_RESET_LIBS})
            unset(Featherkit_${FIND_Featherkit_COMPONENT}_LIBRARY CACHE)
        endif()

        find_library(Featherkit_${FIND_Featherkit_COMPONENT}_LIBRARY
            NAMES ${FIND_Featherkit_COMPONENT_NAME}
            PATH_SUFFIXES lib64 lib
            PATHS ${FIND_Featherkit_LIB_PATHS})
    endif()

    if(NOT Featherkit_${FIND_Featherkit_COMPONENT}_LIBRARY)
        set(FIND_Featherkit_MISSING "${FIND_Featherkit_MISSING} Featherkit_${FIND_Featherkit_COMPONENT}_LIBRARY")
    else()
        set(FEATHERKIT_LIBRARY ${FEATHERKIT_LIBRARY} ${Featherkit_${FIND_Featherkit_COMPONENT}_LIBRARY})
    endif()
endforeach()

find_library(
    FEATHERKIT_LIBRARY
    fea-ui
    PATH_SUFFIXES
    lib
    lib64
    PATHS
    /usr
    /usr/local
    ${FEATHERKIT_ROOT}
    ${FEATHERKITDIR}
    $ENV{FEATHERKITDIR}
    $ENV{FEATHERKIT_ROOT}
)

if(NOT FEATHERKIT_INCLUDE_DIR OR FIND_Featherkit_MISSING)
    set(FEATHERKIT_FOUND)
    set(FEATHERKIT_INCLUDE_DIRS)
    set(FEATHERKIT_LIBRARIES)
    if(Featherkit_FIND_REQUIRED)
        message(FATAL_ERROR "Feather kit not found.")
    elseif(NOT Featherkit_FIND_QUIETLY)
        message(STATUS "Feather kit not found.")
    endif()
else()
    set(FEATHERKIT_FOUND true)
    if(NOT Featherkit_FIND_QUIETLY)
        message(STATUS "Feather kit found: ${FEATHERKIT_INCLUDE_DIR}")
    endif()
    set(FEATHERKIT_INCLUDE_DIRS ${FEATHERKIT_INCLUDE_DIR})
    set(FEATHERKIT_LIBRARIES ${FEATHERKIT_LIBRARY})
endif()
