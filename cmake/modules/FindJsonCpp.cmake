# - Find JsonCpp
# Find the JsonCpp includes and library
# This module defines
#  JSONCPP_INCLUDE_DIRS
#  JSONCPP_LIBRARIES
#  JSONCPP_FOUND

if(JSONCPP_INCLUDE_DIR)
    set(JSONCPP_FIND_QUIETLY TRUE)
endif(JSONCPP_INCLUDE_DIR)

find_path(JSONCPP_INCLUDE_DIR jsoncpp/json/json.h
    /usr/local/include
    /usr/include
    )

set(JSONCPP_NAMES ${JSONCPP_NAMES} libjsoncpp.so)
find_library(JSONCPP_LIBRARY
    NAMES ${JSONCPP_NAMES}
    PATHS /usr/lib /usr/local/lib
    )

if(JSONCPP_LIBRARY AND JSONCPP_INCLUDE_DIR)
    set(JSONCPP_INCLUDE_DIRS ${JSONCPP_INCLUDE_DIR} ${JSONCPP_INCLUDE_DIR}/jsoncpp)
    set(JSONCPP_LIBRARIES ${JSONCPP_LIBRARY})
    set(JSONCPP_FOUND "YES")
else(JSONCPP_LIBRARY AND JSONCPP_INCLUDE_DIR)
    set(JSONCPP_FOUND "NO")
endif(JSONCPP_LIBRARY AND JSONCPP_INCLUDE_DIR)

if(JSONCPP_FOUND)
   if(NOT JSONCPP_FIND_QUIETLY)
      message(STATUS "Found JsonCpp: ${JSONCPP_LIBRARIES}")
   endif (NOT JSONCPP_FIND_QUIETLY)
else(JSONCPP_FOUND)
   if(JsonCpp_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find JsonCpp library")
   endif(JsonCpp_FIND_REQUIRED)
endif(JSONCPP_FOUND)

mark_as_advanced(
    JSONCPP_LIBRARY
    JSONCPP_INCLUDE_DIR
    )
