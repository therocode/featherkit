#cmake ver req
cmake_minimum_required(VERSION 2.8.3)

set(USE_CLANG FALSE CACHE BOOL "Select this if you want to use CLANG")
set(CLANG_PATH "/usr/bin/clang++" CACHE PATH "Path to run CLANG from")
set(DEBUG_BUILD TRUE CACHE BOOL "Turns off optimisation and builds debug info")

set(BUILD_STRUCTURE TRUE CACHE BOOL "Selects if the structure module should be built")
set(BUILD_ENTITY TRUE CACHE BOOL "Selects if the entity module should be built")
set(BUILD_MESSAGING TRUE CACHE BOOL "Selects if the messaging module should be built")
set(BUILD_RENDERING TRUE CACHE BOOL "Selects if the rendering module should be built")
set(BUILD_UI TRUE CACHE BOOL "Selects if the UI module should be built")

set(BUILD_SFMLBACKENDS FALSE CACHE BOOL "Deactivate this if you don't want sfml dependant things to be built")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  #for shared libs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)   #for static libs

#project name
set(project_name windlab)
project(${project_name})

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/")

if(USE_CLANG)
    set(CMAKE_CXX_COMPILER ${CLANG_PATH})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror")

    if(DEBUG_BUILD)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    endif()
else()
    if(MINGW OR CMAKE_COMPILER_IS_GNUCXX)
        #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic") #proper but bad for glm
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror")

        if(DEBUG_BUILD)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
        endif()
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

        if(DEBUG_BUILD)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
        endif()
    endif()
endif()

if(BUILD_STRUCTURE)
    ##Structure module##
    #find all source files
    file(GLOB_RECURSE structure_source_files "src/structure/*.cpp")
    file(GLOB_RECURSE structure_header_files "include/structure/*.h")
    add_library(${project_name}-structure ${structure_header_files} ${structure_source_files})
endif()

if(BUILD_ENTITY)
    ##Entity module##
    #find all source files
    file(GLOB_RECURSE entity_source_files "src/entity/*.cpp")
    file(GLOB_RECURSE entity_header_files "include/framework/entity/*.h")

    file(GLOB_RECURSE entity_util_source_files "src/util/entity/*.cpp")
    file(GLOB_RECURSE entity_util_header_files "include/framework/util/entity/*.h")

    add_library(${project_name}-entity ${entity_header_files} ${entity_source_files} ${entity_util_source_files} ${entity_util_header_files})
endif()

if(BUILD_MESSAGING)
    ##Messaging module##
    #find all source files
    file(GLOB_RECURSE messaging_source_files "src/messaging/*.cpp")
    file(GLOB_RECURSE messaging_header_files "include/framework/messaging/*.h")
    add_library(${project_name}-messaging ${messaging_header_files} ${messaging_source_files})
endif()

if(BUILD_RENDERING)
    ##Rendering module##
    #find all source files
    file(GLOB_RECURSE rendering_source_files "src/rendering/*.cpp")
    file(GLOB_RECURSE rendering_header_files "include/framework/rendering/*.h")

    file(GLOB_RECURSE rendering_util_source_files "src/util/rendering/*.cpp")
    file(GLOB_RECURSE rendering_util_header_files "include/framework/util/rendering/*.h")

    file(GLOB_RECURSE fontstash_source_files "src/fontstash/*.cpp")
    file(GLOB_RECURSE fontstash_header_files "include/framework/fontstash/*.cpp")

    find_package(GLew REQUIRED)
    if(GLEW_FOUND)
        #target_link_libraries(asdf ${GLEW_LIBRARIES})
        include_directories(${GLEW_INCLUDE_DIR})
    endif(GLEW_FOUND)

    add_library(${project_name}-rendering ${rendering_source_files} ${rendering_header_files} ${rendering_util_source_files} ${rendering_util_header_files} ${fontstash_source_files} ${fontstash_header_files})
endif()

if(BUILD_UI)
    ##UI module##
    #find all source files
    file(GLOB_RECURSE ui_source_files "src/window/*.cpp" "src/input/*.cpp")
    file(GLOB_RECURSE ui_header_files "include/framework/window/*.h" "include/framework/input/*.h")

    file(GLOB_RECURSE ui_util_source_files "src/util/input/*.cpp")
    file(GLOB_RECURSE ui_util_header_files "include/framework/util/input/*.h")

    if(${BUILD_SFMLBACKENDS})
        find_package(SFML REQUIRED)
        if(SFML_FOUND)
        #target_link_libraries(asdf ${SFML_LIBRARY})
            include_directories(${SFML_INCLUDE_DIR})
            message("sfml gound here: ${SFML_INCLUDE_DIR}")
        endif(SFML_FOUND)
        file(GLOB_RECURSE ui_sfml_backend_source_files "${CMAKE_CURRENT_LIST_DIR}/src/util/sfml/*cpp")
    endif()
    add_library(${project_name}-ui ${ui_header_files} ${ui_source_files} ${ui_util_source_files} ${ui_util_header_files} ${ui_sfml_backend_source_files})
endif()
