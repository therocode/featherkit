# Locate SFML library 
# This module defines 
# SFML_LIBRARY, the name of the library to link against 
# SFML_FOUND, if false, do not try to link to SFML 
# SFML_INCLUDE_DIR, where to find SFML headers 
# 
# Created by Nils Hasenbanck. Based on the FindSDL_*.cmake modules, 
# created by Eric Wing, which were influenced by the FindSDL.cmake 
# module, but with modifications to recognize OS X frameworks and 
# additional Unix paths (FreeBSD, etc). 
# 
# Changelog: 
# 2010-04-04   Add support for wxWIN with visual studio 2008 (9.0) 

SET( SFMLDIR $ENV{SFMLDIR} ) 
IF(MSVC) 
# Convert backslashes to slashes 
    STRING(REGEX REPLACE "\\\\" "/" SFMLDIR "${SFMLDIR}") 
ENDIF(MSVC) 

    SET(SFML_COMPONENTS 
            System 
            Audio 
            Graphics 
            Network 
            Window 
       ) 

    SET(SFML_INCLUDE_SEARCH_DIR 
            ~/Library/Frameworks 
            /Library/Frameworks 
            /usr/local/include/SFML 
            /usr/include/SFML 
            /usr/local/include 
            /usr/include 
            /sw/include/SFML # Fink 
            /sw/include 
            /opt/local/include/SFML # DarwinPorts 
            /opt/local/include 
            /opt/csw/include/SFML # Blastwave 
            /opt/csw/include 
            /opt/include/SFML 
            /opt/include 
            ${SFMLDIR}/include #for wxWIN vc2008(9.0)
            "C:/program\ files\ \(x86\)/SFML"
       ) 

    SET(SFML_LIBRARY_SEARCH_DIR 
            ~/Library/Frameworks 
            /Library/Frameworks 
            /usr/local 
            /usr 
            /sw 
            /opt/local 
            /opt/csw 
            /opt 
            ${SFMLDIR}/lib
            ${SFMLDIR}/lib/vc2008 #for wxWIN vc2008(9.0) 
            "C:/program files (x86)/SFML/lib"
       ) 

FOREACH(COMPONENT ${SFML_COMPONENTS}) 
STRING(TOUPPER ${COMPONENT} UPPERCOMPONENT) 
STRING(TOLOWER ${COMPONENT} LOWERCOMPONENT) 
    FIND_LIBRARY(SFML_${UPPERCOMPONENT}_LIBRARY 
            NAMES sfml-${LOWERCOMPONENT} 
            PATH_SUFFIXES lib64 lib 
            PATHS ${SFML_LIBRARY_SEARCH_DIR} 
            ) 

    FIND_PATH(SFML_${UPPERCOMPONENT}_INCLUDE_DIR ${COMPONENT}.hpp 
            PATH_SUFFIXES include SFML 
            PATHS ${SFML_INCLUDE_SEARCH_DIR} 
            ) 
IF(MSVC) 
# In wxWIN we need the root include directory without the "/SFML" at the end... so we have to remove it. 
# This is a oversized "remove 5 chars at the right end of the string" function: 
string(LENGTH ${SFML_${UPPERCOMPONENT}_INCLUDE_DIR} STRING_SIZE) 
math(EXPR STRING_SIZE ${STRING_SIZE}-5) 
    string(SUBSTRING "${SFML_${UPPERCOMPONENT}_INCLUDE_DIR}" 0 ${STRING_SIZE} SFML_${UPPERCOMPONENT}_INCLUDE_DIR)    
ENDIF(MSVC) 

IF(SFML_${UPPERCOMPONENT}_INCLUDE_DIR AND SFML_${UPPERCOMPONENT}_LIBRARY) 
LIST(APPEND SFML_LIBRARY ${SFML_${UPPERCOMPONENT}_LIBRARY}) 
LIST(APPEND SFML_INCLUDE_DIR ${SFML_${UPPERCOMPONENT}_INCLUDE_DIR}) 
    LIST(REMOVE_DUPLICATES SFML_LIBRARY) 
    LIST(REMOVE_DUPLICATES SFML_INCLUDE_DIR) 
ENDIF(SFML_${UPPERCOMPONENT}_INCLUDE_DIR AND SFML_${UPPERCOMPONENT}_LIBRARY) 
ENDFOREACH(COMPONENT) 

IF(WIN32) 
#Now we are looking for "sfml-main.lib". 
#Because we need it if we give ADD_EXECUTABLE the WIN32 switch to creat a GUI application (that one without a cmd promt) 
    FIND_LIBRARY( SFML_MAIN_LIBRARY 
            NAMES sfml-main 
            PATH_SUFFIXES lib64 lib 
            PATHS ${SFML_LIBRARY_SEARCH_DIR} 
            )    
LIST(APPEND SFML_LIBRARY ${SFML_MAIN_LIBRARY}) 
ENDIF(WIN32) 

    SET(SFML_FOUND "NO") 
IF(SFML_SYSTEM_LIBRARY AND SFML_INCLUDE_DIR) 
    SET(SFML_FOUND "YES") 
ENDIF(SFML_SYSTEM_LIBRARY AND SFML_INCLUDE_DIR) 

    INCLUDE(FindPackageHandleStandardArgs) 
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SFML DEFAULT_MSG SFML_LIBRARY SFML_INCLUDE_DIR)
