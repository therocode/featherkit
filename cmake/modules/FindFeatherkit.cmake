set( FEATHERKIT_FOUND false)

find_path(
    FEATHERKIT_INCLUDE_DIR
    featherkit/structure.h
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
    /opt)

#list(FIND Featherkit_FIND_COMPONENTS "rendering" Featherkit_NEEDS_GLM)

#if(Featherkit_NEEDS_GLM EQUAL -1)
#    message("i don't need glm!")
#else()
#    message("i need glm!")
#endif()

foreach(FIND_Featherkit_COMPONENT ${Featherkit_FIND_COMPONENTS})
    string(TOLOWER ${FIND_Featherkit_COMPONENT} FIND_Featherkit_COMPONENT)

    set(FIND_Featherkit_COMPONENT_NAME featherkit-${FIND_Featherkit_COMPONENT})

    find_library(Featherkit_${FIND_Featherkit_COMPONENT}_LIBRARY
        NAMES ${FIND_Featherkit_COMPONENT_NAME}
        PATH_SUFFIXES lib64 lib
        PATHS ${FIND_Featherkit_LIB_PATHS})

    if(NOT Featherkit_${FIND_Featherkit_COMPONENT}_LIBRARY)
        set(FIND_Featherkit_MISSING "${FIND_Featherkit_MISSING} Featherkit_${FIND_Featherkit_COMPONENT}_LIBRARY")
    else()
        set(FEATHERKIT_LIBRARY ${FEATHERKIT_LIBRARY} ${Featherkit_${FIND_Featherkit_COMPONENT}_LIBRARY})
    endif()
endforeach()

find_library(
    FEATHERKIT_LIBRARY
    featherkit-ui
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
    set(FAETHERKIT_LIBRARIES)
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
