#cmake ver req
cmake_minimum_required(VERSION 2.8.3)

set(BUILD_GALE_TESTS FALSE CACHE BOOL "Build gale test applications?")
set(IGNORE_SFML_TESTS FALSE CACHE BOOL "Ignore tests using sfml?")
set(USE_CLANG FALSE CACHE BOOL "Select this if you want to use CLANG")
set(CLANG_PATH "/usr/bin/clang++" CACHE PATH "Path to run CLANG from")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   #for executables

if(USE_CLANG)
    set(CMAKE_CXX_COMPILER ${CLANG_PATH})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    if(BUILD_GALE_STRICT)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
    endif()
    if(BUILD_GALE_DEBUG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    endif()
else()
    if(UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

        if(BUILD_GALE_STRICT)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
        endif()

        if(BUILD_GALE_DEBUG)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
        endif()
    endif()
endif()

add_subdirectory(gale)
add_subdirectory(breeze)

#project name
set(project_name windlab)
project(${project_name})

link_directories("${CMAKE_BINARY_DIR}/lib")

##test section##

if(BUILD_GALE_TESTS)

    include_directories("gale/src")
    include_directories("breeze/src")

    if(NOT IGNORE_SFML_TESTS)
        file(GLOB_RECURSE particles_source_files "test/particles/*.cpp")
        file(GLOB_RECURSE particles_header_files "test/particles/*.h")

        add_executable(${project_name}_particles ${particles_header_files} ${particles_source_files})
        target_link_libraries(${project_name}_particles windgale libsfml-graphics.so)

        file(GLOB_RECURSE entity_source_files "test/entitytest/*.cpp")
        file(GLOB_RECURSE entity_header_files "test/entitytest/*.h")

        add_executable(${project_name}_entity ${entity_header_files} ${entity_source_files})
        target_link_libraries(${project_name}_entity windgale libsfml-graphics.so)

        file(GLOB_RECURSE texttest_source_files "test/texttest/*.cpp")
        file(GLOB_RECURSE texttest_header_files "test/texttest/*.h")

        add_executable(${project_name}_texttest ${texttest_header_files} ${texttest_source_files})
        target_link_libraries(${project_name}_texttest windgale libsfml-graphics.so)
    endif()
endif()
