#cmake ver req
cmake_minimum_required(VERSION 2.8.3)

set(SHARED_BUILD TRUE CACHE BOOL "Set this to false if you want a static build")

set(BUILD_STRUCTURE TRUE CACHE BOOL "Selects if the structure module should be built")
set(BUILD_ENTITY TRUE CACHE BOOL "Selects if the entity module should be built")
set(BUILD_MESSAGING TRUE CACHE BOOL "Selects if the messaging module should be built")
set(BUILD_RENDERING TRUE CACHE BOOL "Selects if the rendering module should be built")
set(BUILD_UI TRUE CACHE BOOL "Selects if the UI module should be built")

set(BUILD_SFMLBACKENDS FALSE CACHE BOOL "Selects if the SFML backends should be built")
set(BUILD_OPENGLBACKENDS FALSE CACHE BOOL "Selects if the OpenGL rendering backends should be built")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  #for shared libs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)   #for static libs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   #for static libs

if(SHARED_BUILD)
    set(SHARED_OR_STATIC SHARED)
else(SHARED_BUILD)
    set(SHARED_OR_STATIC STATIC)
endif(SHARED_BUILD)

#project name
set(project_name featherkit)
project(${project_name})

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/")

#if(MINGW OR CMAKE_COMPILER_IS_GNUCXX OR Clang)
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic") #proper but bad for glm
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror")
#endif()

if(BUILD_STRUCTURE)
    ##Structure module##
    #find all source files
    file(GLOB structure_source_files "src/structure/*.cpp")
    file(GLOB structure_header_files "include/structure/*.h")
    add_library(${project_name}-structure ${SHARED_OR_STATIC} ${structure_header_files} ${structure_source_files})
endif()

if(BUILD_ENTITY)
    ##Entity module##
    #find all source files
    file(GLOB entity_source_files "src/entity/*.cpp")
    file(GLOB entity_header_files "include/featherkit/entity/*.h")

    file(GLOB entity_util_source_files "src/util/entity/*.cpp")
    file(GLOB entity_util_header_files "include/featherkit/util/entity/*.h")
    set(entity_util_source_files ${entity_util_source_files} "src/util/filenotfoundexception.cpp")
    set(entity_util_header_files ${entity_util_header_files} "include/featherkit/util/filenotfoundexception.h")

    add_library(${project_name}-entity ${SHARED_OR_STATIC} ${entity_header_files} ${entity_source_files} ${entity_util_source_files} ${entity_util_header_files})
endif()

if(BUILD_MESSAGING)
    ##Messaging module##
    #find all source files
    file(GLOB messaging_source_files "src/messaging/*.cpp")
    file(GLOB messaging_header_files "include/featherkit/messaging/*.h")
    add_library(${project_name}-messaging ${SHARED_OR_STATIC} ${messaging_header_files} ${messaging_source_files})
endif()

if(BUILD_RENDERING)
    ##Rendering module##
    #find all source files
    file(GLOB rendering_source_files "src/rendering/*.cpp")
    file(GLOB rendering_header_files "include/featherkit/rendering/*.h")

    file(GLOB rendering_util_source_files "src/util/rendering/*.cpp")
    file(GLOB rendering_util_header_files "include/featherkit/util/rendering/*.h")

    file(GLOB fontstash_source_files "src/fontstash/*.cpp")
    file(GLOB fontstash_header_files "include/featherkit/fontstash/*.cpp")
    
    if(${BUILD_OPENGLBACKENDS})
        find_package(OpenGL REQUIRED)
        if(OPENGL_FOUND)
            include_directories(${OPENGL_INCLUDE_DIR})
        endif(OPENGL_FOUND)
        find_package(GLew REQUIRED)
        if(GLEW_FOUND)
            include_directories(${GLEW_INCLUDE_DIR})
        endif(GLEW_FOUND)

        file(GLOB rendering_opengl_backend_source_files "src/util/rendering/opengl/*.cpp" "src/util/rendering/opengl/*.cpp")
        file(GLOB rendering_opengl_backend_header_files "include/featherkit/util/rendering/opengl/*.h" "include/featherkit/util/rendering/opengl/*.h")
    endif()

    add_library(${project_name}-rendering ${SHARED_OR_STATIC} ${rendering_source_files} ${rendering_header_files} ${rendering_util_source_files} ${rendering_util_header_files} ${fontstash_source_files} ${fontstash_header_files} ${rendering_opengl_backend_source_files} ${rendering_opengl_backend_header_files} ${GLEW_LIBRARIES})

    if(${BUILD_OPENGLBACKENDS})
        if(GLEW_FOUND)
            target_link_libraries(${project_name}-rendering ${GLEW_LIBRARIES})
        endif(GLEW_FOUND)
        if(OPENGL_FOUND)
            target_link_libraries(${project_name}-rendering ${OPENGL_LIBRARIES})
        endif(OPENGL_FOUND)
    endif()
endif()

if(BUILD_UI)
    ##UI module##
    #find all source files
    file(GLOB ui_source_files "src/window/*.cpp" "src/input/*.cpp")
    file(GLOB ui_header_files "include/featherkit/window/*.h" "include/featherkit/input/*.h")

    file(GLOB ui_util_source_files "src/util/window/*.cpp" "src/util/input/*.cpp")
    file(GLOB ui_util_header_files "include/featherkit/util/window/*.h" "include/featherkit/util/input/*.h")

    if(${BUILD_SFMLBACKENDS})
        find_package(SFML COMPONENTS window system REQUIRED)
        if(SFML_FOUND)
            include_directories(${SFML_INCLUDE_DIR})
        endif(SFML_FOUND)
        file(GLOB ui_sfml_backend_source_files "src/util/window/sfml/*.cpp" "src/util/input/sfml/*.cpp")
        file(GLOB ui_sfml_backend_header_files "include/featherkit/util/window/sfml/*.h" "include/featherkit/util/input/sfml/*.h")
    endif()

    add_library(${project_name}-ui ${SHARED_OR_STATIC} ${ui_header_files} ${ui_source_files} ${ui_util_source_files} ${ui_util_header_files} ${ui_sfml_backend_source_files} ${ui_sfml_backend_header_files})

    if(${BUILD_SFMLBACKENDS})
        if(SFML_FOUND)
            target_link_libraries(${project_name}-ui ${SFML_LIBRARIES})
        endif()
    endif()
endif()
