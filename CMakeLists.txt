#cmake ver req
cmake_minimum_required(VERSION 2.8.3)

set(BUILD_GALE TRUE CACHE BOOL "Selects if gale should be built")
set(BUILD_BREEZE TRUE CACHE BOOL "Selects if breeze should be built")
set(BUILD_STORM TRUE CACHE BOOL "Selects if storm should be built")
set(BUILD_TESTS FALSE CACHE BOOL "Build gale test applications?")
set(BUILD_TESTS_STRICT TRUE CACHE BOOL "Makes use of the -Wall -Wextra and -Werror flags")
set(BUILD_TESTS_DEBUG TRUE CACHE BOOL "Turns off optimisation and builds debug info")
set(COMMANDLINE_TESTS_ONLY FALSE CACHE BOOL "Ignore tests using sfml?")
set(USE_CLANG FALSE CACHE BOOL "Select this if you want to use CLANG")
set(CLANG_PATH "/usr/bin/clang++" CACHE PATH "Path to run CLANG from")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   #for executables


if(BUILD_GALE)
    add_subdirectory(gale)
endif()
if(BUILD_BREEZE)
    add_subdirectory(breeze)
endif()
if(BUILD_STORM)
    add_subdirectory(storm)
endif()

#project name
set(project_name windlab)
project(${project_name})

if(USE_CLANG)
    set(CMAKE_CXX_COMPILER ${CLANG_PATH})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

    if(BUILD_TESTS_STRICT)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-parameter")
    endif()
    if(BUILD_TESTS_DEBUG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    endif()
else()
    if(UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

        if(BUILD_TESTS_STRICT)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-parameter")
        endif()

        if(BUILD_TESTS_DEBUG)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
        endif()
    endif()
endif()
link_directories("${CMAKE_BINARY_DIR}/lib")

##test section##

if(BUILD_TESTS)

    include_directories("gale/src")
    include_directories("breeze/src")
    include_directories("storm/src")

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
