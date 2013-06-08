#cmake ver req
cmake_minimum_required(VERSION 2.8.3)

set(USE_CLANG FALSE CACHE BOOL "Select this if you want to use CLANG")
set(CLANG_PATH "/usr/bin/clang++" CACHE PATH "Path to run CLANG from")
set(STRICT_BUILD TRUE CACHE BOOL "Makes use of the -Wall -Wextra and -Werror flags")
set(DEBUG_BUILD TRUE CACHE BOOL "Turns off optimisation and builds debug info")

set(BUILD_APP TRUE CACHE BOOL "Selects if the application module should be built")
set(BUILD_ENTITY TRUE CACHE BOOL "Selects if the entity module should be built")
set(BUILD_MESSAGING TRUE CACHE BOOL "Selects if the messaging module should be built")
set(BUILD_RENDERING TRUE CACHE BOOL "Selects if the rendering module should be built")
set(BUILD_UI TRUE CACHE BOOL "Selects if the UI module should be built")

set(BUILD_SFMLBACKENDS FALSE CACHE BOOL "Deactivate this if you don't want sfml dependant things to be built")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   #for executables
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  #for shared libs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)   #for static libs

#project name
set(project_name windlab)
project(${project_name})

include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
set(EXT_LIBS)

#set(CMAKE_CXX_COMPILER g++-4.8)

if(USE_CLANG)
    set(CMAKE_CXX_COMPILER ${CLANG_PATH})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

    if(STRICT_BUILD)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")
    endif()
    if(DEBUG_BUILD)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    endif()
else()
    if(UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

        if(STRICT_BUILD)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")
        endif()

        if(DEBUG_BUILD)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
        endif()
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        include_directories("C:/Program Files (x86)/SFML/include")

        if(DEBUG_BUILD)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
        endif()
    endif()
endif()

if(BUILD_APP)
    ##Application module##
    #find all source files
    file(GLOB_RECURSE app_source_files "src/application/*.cpp")
    file(GLOB_RECURSE app_header_files "include/application/*.h")
    add_library(${project_name}-app ${app_header_files} ${app_source_files})
endif()

if(BUILD_ENTITY)
    ##Entity module##
    #find all source files
    file(GLOB_RECURSE entity_source_files "src/entity/*.cpp")
    file(GLOB_RECURSE entity_header_files "include/entity/*.h")

    file(GLOB_RECURSE entity_util_source_files "src/util/entity/*.cpp")

    add_library(${project_name}-entity ${entity_header_files} ${entity_source_files} ${entity_util_source_files})
endif()

if(BUILD_MESSAGING)
    ##Messaging module##
    #find all source files
    file(GLOB_RECURSE messaging_source_files "src/messaging/*.cpp")
    file(GLOB_RECURSE messaging_header_files "include/messaging/*.h")
    add_library(${project_name}-messaging ${messaging_header_files} ${messaging_source_files})
endif()

if(BUILD_RENDERING)
    ##Rendering module##
    #find all source files
    file(GLOB_RECURSE rendering_source_files "src/rendering/*.cpp")
    file(GLOB_RECURSE rendering_header_files "include/rendering/*.h")
    add_library(${project_name}-rendering ${rendering_header_files} ${rendering_source_files})
endif()

if(BUILD_UI)
    ##UI module##
    #find all source files
    file(GLOB_RECURSE ui_source_files "src/window/*.cpp" "src/input/*.cpp")
    file(GLOB_RECURSE ui_header_files "include/window/*.h" "include/input/*.h")

    file(GLOB_RECURSE ui_util_source_files "src/util/input/*.cpp")

    if(${BUILD_SFMLBACKENDS})
        file(GLOB_RECURSE ui_sfml_backend_source_files "${CMAKE_CURRENT_LIST_DIR}/src/util/sfml/*cpp")
        set(EXT_LIBS libsfml-graphics.so)
    endif()
    add_library(${project_name}-ui ${ui_header_files} ${ui_source_files} ${ui_util_source_files} ${ui_sfml_backend_source_files})
endif()
