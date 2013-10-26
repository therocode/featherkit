#cmake ver req
cmake_minimum_required(VERSION 2.8.3)

if(NOT CMAKE_BUILD_TYPE )
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Select if you want to build Debug or Release" FORCE )
endif()

#project name
set(project_name featherkit)
project(${project_name})

set(SHARED_BUILD TRUE CACHE BOOL "Set this to false if you want a static build")

set(BUILD_STRUCTURE TRUE CACHE BOOL "Selects if the structure module should be built")
set(BUILD_ENTITY TRUE CACHE BOOL "Selects if the entity module should be built")
set(BUILD_MESSAGING TRUE CACHE BOOL "Selects if the messaging module should be built")
set(BUILD_RENDERING FALSE CACHE BOOL "Selects if the rendering module should be built")
set(BUILD_UI TRUE CACHE BOOL "Selects if the UI module should be built")

set(BUILD_SFMLBACKENDS FALSE CACHE BOOL "Selects if the SFML backends should be built")
set(BUILD_SDLBACKENDS FALSE CACHE BOOL "Selects if the SDL backends should be built")
set(BUILD_SDL2BACKENDS TRUE CACHE BOOL "Selects if the SDL2 backends should be built")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  #for shared libs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)   #for static libs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   #for static libs

if(SHARED_BUILD)
    set(SHARED_OR_STATIC SHARED)
else(SHARED_BUILD)
    set(SHARED_OR_STATIC STATIC)
endif(SHARED_BUILD)

if(WIN32)
    set(FEATHERKIT_MISC_DIR .)
    set(WINFIX SYSTEM)
else()
    set(FEATHERKIT_MISC_DIR share/featherkit)
endif()

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/")

#if(MINGW OR CMAKE_COMPILER_IS_GNUCXX OR Clang)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wshadow -Wconversion -Wno-long-long -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#endif()

if(BUILD_STRUCTURE)
    ##Structure module##

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-structure)
    #find all source files
    file(GLOB structure_source_files "src/structure/*.cpp")
    file(GLOB structure_header_files "include/structure/*.h")
    add_library(${project_name}-structure ${SHARED_OR_STATIC} ${structure_header_files} ${structure_source_files})
endif()

if(BUILD_ENTITY)
    ##Entity module##

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-entity)
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

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-messaging)
    #find all source files
    file(GLOB messaging_source_files "src/messaging/*.cpp")
    file(GLOB messaging_header_files "include/featherkit/messaging/*.h")
    add_library(${project_name}-messaging ${SHARED_OR_STATIC} ${messaging_header_files} ${messaging_source_files})
endif()

if(BUILD_RENDERING)
    ##Rendering module##

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-rendering)
    #find all source files
    file(GLOB rendering_source_files "src/rendering/*.cpp")
    file(GLOB rendering_header_files "include/featherkit/rendering/*.h")

    file(GLOB rendering_util_source_files "src/util/rendering/*.cpp")
    file(GLOB rendering_util_header_files "include/featherkit/util/rendering/*.h")

    file(GLOB freetype-gl_source_files "src/freetype-gl/*.c")
    file(GLOB freetype-gl_header_files "include/featherkit/freetype-gl/*.h")

    find_package(GLM REQUIRED)
    if(GLM_FOUND)
        include_directories(${WINFIX} ${GLM_INCLUDE_DIRS})
    endif()
    
    find_package(OpenGL REQUIRED)
    if(OPENGL_FOUND)
        include_directories(${OPENGL_INCLUDE_DIRS})
    endif(OPENGL_FOUND)
    find_package(GLew)
    if(GLEW_FOUND)
        include_directories(${GLEW_INCLUDE_DIRS})
	else(GLEW_FOUND)
		include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/glew/include)
		set(glew_files ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/glew/glew.c ${glew_files})
    endif(GLEW_FOUND)

    file(GLOB rendering_opengl_backend_source_files "src/util/rendering/opengl/*.cpp" "src/util/rendering/opengl/*.cpp")
    file(GLOB rendering_opengl_backend_header_files "include/featherkit/util/rendering/opengl/*.h" "include/featherkit/util/rendering/opengl/*.h")

    add_library(${project_name}-rendering ${SHARED_OR_STATIC} ${glew_files} ${rendering_source_files} ${rendering_header_files} ${rendering_util_source_files} ${rendering_util_header_files} ${freetype-gl_source_files} ${freetype-gl_header_files} ${rendering_opengl_backend_source_files} ${rendering_opengl_backend_header_files})

    FIND_PACKAGE( Freetype REQUIRED )
    include_directories(${FREETYPE_INCLUDE_DIRS})

    target_link_libraries(${project_name}-rendering ${FREETYPE_LIBRARY} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

endif()

find_package(GLM)
if(GLM_FOUND)
	include_directories(${GLM_INCLUDE_DIRS})
else(GLM_FOUND)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/glm)
endif(GLM_FOUND)

if(BUILD_UI)
    ##UI module##

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-ui)

    #find all source files
    file(GLOB ui_source_files "src/window/*.cpp" "src/input/*.cpp")
    file(GLOB ui_header_files "include/featherkit/window/*.h" "include/featherkit/input/*.h")

    file(GLOB ui_util_source_files "src/util/window/*.cpp" "src/util/input/*.cpp")
    file(GLOB ui_util_header_files "include/featherkit/util/window/*.h" "include/featherkit/util/input/*.h")

    if(${BUILD_SFMLBACKENDS})
        find_package(SFML 2.0 COMPONENTS window system REQUIRED)
        if(SFML_FOUND)
            include_directories(${SFML_INCLUDE_DIR})
        endif(SFML_FOUND)
        file(GLOB ui_sfml_backend_source_files "src/util/window/sfml/*.cpp" "src/util/input/sfml/*.cpp")
        file(GLOB ui_sfml_backend_header_files "include/featherkit/util/window/sfml/*.h" "include/featherkit/util/input/sfml/*.h")
    endif()

    if(${BUILD_SDLBACKENDS})
        find_package(SDL REQUIRED)
        if(SDL_FOUND)
            include_directories(${SDL_INCLUDE_DIR})
        endif(SDL_FOUND)
        file(GLOB ui_sdl_backend_source_files "src/util/window/sdl/*.cpp" "src/util/input/sdl/*.cpp")
        file(GLOB ui_sdl_backend_header_files "include/featherkit/util/window/sdl/*.h" "include/featherkit/util/input/sdl/*.h")
    endif()

	if(${BUILD_SDL2BACKENDS})
		find_package(SDL2)
		if(SDL2_FOUND)
			include_directories(${SDL2_INCLUDE_DIR})
		else(SDL2_FOUND)
			message("Linked dir ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/SDL-2.0/lib")
			link_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/SDL-2.0/lib)
			include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/SDL-2.0/include)
		endif(SDL2_FOUND)
        file(GLOB ui_sdl_backend_source_files "src/util/window/sdl2/*.cpp" "src/util/input/sdl2/*.cpp")
        file(GLOB ui_sdl_backend_header_files "include/featherkit/util/window/sdl2/*.h" "include/featherkit/util/input/sdl2/*.h")
	endif()

	find_package(GLew)
    if(GLEW_FOUND)
        include_directories(${GLEW_INCLUDE_DIRS})
	else(GLEW_FOUND)
		include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/glew/include)
		set(glew_file ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/glew/glew.c ${glew_file})
    endif(GLEW_FOUND)
	
    add_library(${project_name}-ui ${SHARED_OR_STATIC} ${glew_file} ${ui_header_files} ${ui_source_files} ${ui_util_source_files} ${ui_util_header_files} ${ui_sfml_backend_source_files} ${ui_sfml_backend_header_files} ${ui_sdl_backend_source_files} ${ui_sdl_backend_header_files})

    if(${BUILD_SFMLBACKENDS})
        if(SFML_FOUND)
            target_link_libraries(${project_name}-ui ${SFML_LIBRARIES})
        endif()
    endif()
    if(${BUILD_SDLBACKENDS})
        if(SDL_FOUND)
            target_link_libraries(${project_name}-ui ${SDL_LIBRARY})
        endif()
    endif()
	if(${BUILD_SDL2BACKENDS})
		if(SDL2_FOUND)
			target_link_libraries(${project_name}-ui ${SDL2_LIBRARY})
		else(SDL2_FOUND)
			target_link_libraries(${project_name}-ui opengl32 SDL2)
		endif()
	endif()
endif()

install(
    DIRECTORY include
    DESTINATION .
)
 
install(
    TARGETS ${BUILT_TARGETS}
    RUNTIME DESTINATION bin COMPONENT bin
    LIBRARY DESTINATION lib COMPONENT bin
    ARCHIVE DESTINATION lib COMPONENT dev
)

install(
    FILES readme.txt license.txt
    DESTINATION ${FEATHERKIT_MISC_DIR}
)
