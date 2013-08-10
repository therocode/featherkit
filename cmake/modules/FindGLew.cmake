# - Find GLew
# Finds the native GLew headers and libraries
#
#  GLEW_INCLUDE_DIR -  where to find GLew.h
#  GLEW_LIBRARIES    - List of libraries when using GLew.
#  GLEW_FOUND        - True if GLew found.

# Look for the header file.
FIND_PATH( GLEW_INCLUDE_DIR NAMES GL/glew.h
        PATHS /usr/local/include
        $ENV{H3D_EXTERNAL_ROOT}/include  
        DOC "Path in which the file GLew.h is located." )

#MARK_AS_ADVANCED(GLEW_INCLUDE_DIR)

# Look for the library.
# Does this work on UNIX systems? (LINUX)
    FIND_LIBRARY( GLEW_LIBRARY NAMES GLEW
            DOC "Path to the GLew library." )
#MARK_AS_ADVANCED(GLEW_LIBRARY)

# Copy the results to the output variables.
IF(GLEW_INCLUDE_DIR AND GLEW_LIBRARY)
    SET(GLEW_FOUND 1)
    SET(GLEW_LIBRARIES ${GLEW_LIBRARY})
    SET(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
ELSE(GLEW_INCLUDE_DIR AND GLEW_LIBRARY)
    SET(GLEW_FOUND 0)
    SET(GLEW_LIBRARIES)
    SET(GLEW_INCLUDE_DIRS)
ENDIF(GLEW_INCLUDE_DIR AND GLEW_LIBRARY)

# Report the results.
IF(NOT GLEW_FOUND)
    SET(GLEW_DIR_MESSAGE
            "GLEW was not found. Make sure GLEW_LIBRARY and GLEW_INCLUDE_DIR are set.")
IF(GLEW_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "${GLEW_DIR_MESSAGE}")
ELSEIF(NOT GLEW_FIND_QUIETLY)
    MESSAGE(STATUS "${GLEW_DIR_MESSAGE}")
    ENDIF(GLEW_FIND_REQUIRED)
ENDIF(NOT GLEW_FOUND)
