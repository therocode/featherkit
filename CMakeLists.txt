#cmake ver req
cmake_minimum_required(VERSION 2.8.3)

set(USE_CLANG FALSE CACHE BOOL "Select this if you want to use CLANG")
set(CLANG_PATH "/usr/bin/clang++" CACHE PATH "Path to run CLANG from")
set(BUILD_STRICT TRUE CACHE BOOL "Makes use of the -Wall -Wextra and -Werror flags")
set(BUILD_DEBUG TRUE CACHE BOOL "Turns off optimisation and builds debug info")

set(BUILD_GALE TRUE CACHE BOOL "Selects if gale should be built")
set(BUILD_BREEZE TRUE CACHE BOOL "Selects if breeze should be built")
set(BUILD_STORM TRUE CACHE BOOL "Selects if storm should be built")

set(BUILD_SFMLBACKENDS FALSE CACHE BOOL "Deactivate this if you don't want sfml dependant things to be built")

set(BUILD_TESTS FALSE CACHE BOOL "Build test applications?")
set(COMMANDLINE_TESTS_ONLY FALSE CACHE BOOL "Ignore tests using sfml?")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   #for executables
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  #for shared libs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)   #for static libs

#project name
set(project_name windlab)
project(${project_name})

include_directories(${CMAKE_CURRENT_LIST_DIR})

if(USE_CLANG)
    set(CMAKE_CXX_COMPILER ${CLANG_PATH})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

    if(BUILD_STRICT)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-parameter")
    endif()
    if(BUILD_DEBUG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    endif()
else()
    if(UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

        if(BUILD_STRICT)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-parameter")
        endif()

        if(BUILD_DEBUG)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
        endif()
    endif()
endif()

if(BUILD_STORM)
    ##storm section##
    #find all source files
    file(GLOB_RECURSE storm_source_files "src/storm/*.cpp")
    file(GLOB_RECURSE storm_header_files "include/storm/*.h")
    add_library(${project_name}-storm ${storm_header_files} ${storm_source_files})
endif()

if(BUILD_GALE)
    ##gale section##
    #find all source files
    include_directories("gale")
    file(GLOB_RECURSE gale_source_files "src/gale/*.cpp")
    file(GLOB_RECURSE gale_header_files "include/gale/*.h")
    add_library(${project_name}-gale ${gale_header_files} ${gale_source_files})
endif()

if(BUILD_BREEZE)
    ##breeze section##
    #find all source files
    file(GLOB_RECURSE breeze_source_files "src/breeze/*.cpp")
    file(GLOB_RECURSE breeze_header_files "include/breeze/*.h")

    if(NOT ${BUILD_BREEZE_SFMLBACKEND})
        list(REMOVE_ITEM breeze_source_files "${CMAKE_CURRENT_LIST_DIR}/src/breeze/sfmleventbackend.cpp")
        list(REMOVE_ITEM breeze_source_files "${CMAKE_CURRENT_LIST_DIR}/src/breeze/sfmlwindowbackend.cpp")
    endif()
endif()

add_library(${project_name}-breeze ${breeze_header_files} ${breeze_source_files})

##test section##
if(BUILD_TESTS)
    link_directories("${CMAKE_BINARY_DIR}/lib")
    include_directories("include")

    if(NOT COMMANDLINE_TESTS_ONLY)
        file(GLOB_RECURSE particles_source_files "test/particles/*.cpp")
        file(GLOB_RECURSE particles_header_files "test/particles/*.h")

        add_executable(${project_name}_particles ${particles_header_files} ${particles_source_files})
        target_link_libraries(${project_name}_particles windgale windbreeze windstorm libsfml-graphics.so)
    endif()

    file(GLOB_RECURSE entity_source_files "test/entitytest/*.cpp")
    file(GLOB_RECURSE entity_header_files "test/entitytest/*.h")

    add_executable(${project_name}_entity ${entity_header_files} ${entity_source_files})
    target_link_libraries(${project_name}_entity windgale windbreeze windstorm libsfml-graphics.so)

    file(GLOB_RECURSE texttest_source_files "test/texttest/*.cpp")
    file(GLOB_RECURSE texttest_header_files "test/texttest/*.h")

    add_executable(${project_name}_texttest ${texttest_header_files} ${texttest_source_files})
    target_link_libraries(${project_name}_texttest windgale windbreeze windstorm libsfml-graphics.so)
endif()
