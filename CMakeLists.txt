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
set(BUILD_RENDERING TRUE CACHE BOOL "Selects if the rendering module should be built")
set(BUILD_UI TRUE CACHE BOOL "Selects if the UI module should be built")

set(BUILD_SFMLBACKENDS FALSE CACHE BOOL "Selects if the SFML backends should be built")
set(BUILD_SDLBACKENDS FALSE CACHE BOOL "Selects if the SDL backends should be built")
set(BUILD_SDL2BACKENDS FALSE CACHE BOOL "Selects if the SDL2 backends should be built")

set(SDK_PATH "" CACHE PATH "Optional path to the Featherkit SDK. If this is not set, the dependencies have to be handled manually.")

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

    set(structure_source_files 
        src/structure/application.cpp
        src/structure/gamestatemachine.cpp)

    set(structure_header_files include/featherkit/structure/application.h
        include/featherkit/structure/gamestate.h
        include/featherkit/structure/gamestatemachine.h)

    add_library(${project_name}-structure ${SHARED_OR_STATIC} ${structure_header_files} ${structure_source_files})
endif()

if(BUILD_ENTITY)
    ##Entity module##

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-entity)

    set(entity_source_files
        src/entity/entity.cpp
        src/entity/entityfactory.cpp
        src/entity/entitystorage.cpp
        src/entity/entityexceptions.cpp
        src/entity/entitymanager.cpp)

    set(entity_header_files 
        include/featherkit/entity/entityexceptions.h
        include/featherkit/entity/entityfactory.h
        include/featherkit/entity/entity.h
        include/featherkit/entity/entitymanager.h
        include/featherkit/entity/entitystorage.h)

    set(entity_util_source_files
        src/util/entity/defaultsetters.cpp
        src/util/entity/jsonentityloader.cpp
        src/util/filenotfoundexception.cpp)
    set(entity_util_header_files
        include/featherkit/util/entity/defaultsetters.h
        include/featherkit/util/entity/jsonentityloader.h
        include/featherkit/util/filenotfoundexception.h)

    add_library(${project_name}-entity ${SHARED_OR_STATIC} ${entity_header_files} ${entity_source_files} ${entity_util_source_files} ${entity_util_header_files})
endif()

if(BUILD_MESSAGING)
    ##Messaging module##

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-messaging)

    set(messaging_source_files 
        src/messaging/messagebus.cpp
        src/messaging/messageexception.cpp)

    set(messaging_header_files 
        include/featherkit/messaging/messagebus.h
        include/featherkit/messaging/messageexception.h
        include/featherkit/messaging/message.h
        include/featherkit/messaging/messagereceiver.h)
    add_library(${project_name}-messaging ${SHARED_OR_STATIC} ${messaging_header_files} ${messaging_source_files})
endif()

if(BUILD_RENDERING)
    set(BUILD_RENDERING_TEXT TRUE CACHE BOOL "Selects if text rendering should be built (requires freetype2)")
    ##Rendering module##

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-rendering)

    set(rendering_source_files 
        src/rendering/animatedquad.cpp
        src/rendering/animation.cpp
        src/rendering/camera.cpp
        src/rendering/colour.cpp
        src/rendering/defaultshader.cpp
        src/rendering/drawable2d.cpp
        src/rendering/projection.cpp
        src/rendering/quad.cpp
        src/rendering/renderer2d.cpp
        src/rendering/rendertarget.cpp
        src/rendering/repeatedquad.cpp
        src/rendering/shader.cpp
        src/rendering/subrectquad.cpp
        src/rendering/texture.cpp
        src/rendering/tilechunk.cpp
        src/rendering/tilemap.cpp
        src/rendering/uniform.cpp
        src/rendering/vertexattribute.cpp
        src/rendering/viewport.cpp)

    set(rendering_header_files 
        include/featherkit/rendering/animatedquad.h
        include/featherkit/rendering/animation.h
        include/featherkit/rendering/camera.h
        include/featherkit/rendering/colour.h
        include/featherkit/rendering/defaultshader.h
        include/featherkit/rendering/drawable2d.h
        include/featherkit/rendering/opengl.h
        include/featherkit/rendering/projection.h
        include/featherkit/rendering/quad.h
        include/featherkit/rendering/renderer2d.h
        include/featherkit/rendering/renderinfo.h
        include/featherkit/rendering/rendertarget.h
        include/featherkit/rendering/repeatedquad.h
        include/featherkit/rendering/shader.h
        include/featherkit/rendering/subrectquad.h
        include/featherkit/rendering/texture.h
        include/featherkit/rendering/tilechunk.h
        include/featherkit/rendering/tilemap.h
        include/featherkit/rendering/uniform.h
        include/featherkit/rendering/vertexattribute.h
        include/featherkit/rendering/viewport.h)

    if(BUILD_RENDERING_TEXT)
        set(freetype-gl_source_files 
            src/freetype-gl/platform.c
            src/freetype-gl/texture-atlas.c
            src/freetype-gl/texture-font.c
            src/freetype-gl/vector.c)

        set(freetype-gl_header_files 
            include/featherkit/freetype-gl/platform.h
            include/featherkit/freetype-gl/texture-atlas.h
            include/featherkit/freetype-gl/texture-font.h
            include/featherkit/freetype-gl/vec234.h
            include/featherkit/freetype-gl/vector.h)
    endif(BUILD_RENDERING_TEXT)


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
	elseif(SDK_PATH)
        add_definitions(-DGLEW_STATIC)
		include_directories(${SDK_PATH}/glew/include)
		set(glew_files ${SDK_PATH}/glew/glew.c ${glew_files})
        add_definitions(GLEW_STATIC)
    endif(GLEW_FOUND)

    add_library(${project_name}-rendering ${SHARED_OR_STATIC} ${glew_files} ${rendering_source_files} ${rendering_header_files} ${freetype-gl_source_files} ${freetype-gl_header_files})

    if(BUILD_RENDERING_TEXT)
        FIND_PACKAGE( Freetype REQUIRED )
        include_directories(${FREETYPE_INCLUDE_DIRS})
    endif(BUILD_RENDERING_TEXT)

    target_link_libraries(${project_name}-rendering ${FREETYPE_LIBRARY} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

endif()

if(BUILD_UI)
    ##UI module##

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-ui)

    #find all source files
    set(ui_source_files 
        src/input/actiontrigger.cpp
        src/input/inputhandler.cpp
        src/window/contextsettings.cpp
        src/window/videomode.cpp
        src/window/window.cpp)

    set(ui_header_files 
        include/featherkit/window/contextsettings.h
        include/featherkit/window/vec2i.h
        include/featherkit/window/videomode.h
        include/featherkit/window/windowbackend.h
        include/featherkit/window/window.h
        include/featherkit/window/windowstyle.h
        include/featherkit/input/actionhandler.h
        include/featherkit/input/actiontrigger.h
        include/featherkit/input/event.h
        include/featherkit/input/gamepad.h
        include/featherkit/input/inputbackend.h
        include/featherkit/input/inputhandler.h
        include/featherkit/input/keyboard.h
        include/featherkit/input/mouse.h)

    set(ui_util_header_files 
        include/featherkit/util/input/jsonactioniohandler.h)

    if(${BUILD_SFMLBACKENDS})
        find_package(SFML 2.0 COMPONENTS window system REQUIRED)
        if(SFML_FOUND)
            include_directories(${SFML_INCLUDE_DIR})
        endif(SFML_FOUND)
        set(ui_sfml_backend_source_files 
            src/util/window/sfmlwindowbackend.cpp
            src/util/input/sfmlinputbackend.cpp)

        set(ui_sfml_backend_header_files
            include/featherkit/util/window/sfmlwindowbackend.h
            include/featherkit/util/input/sfmlinputbackend.h)
    endif()

    if(${BUILD_SDLBACKENDS})
        find_package(SDL REQUIRED)
        if(SDL_FOUND)
            include_directories(${SDL_INCLUDE_DIR})
        endif(SDL_FOUND)
        set(ui_sdl_backend_source_files 
            src/util/window/sdlwindowbackend.cpp
            src/util/input/sdlinputbackend.cpp)

        set(ui_sdl_backend_header_files
        include/featherkit/util/window/sdlwindowbackend.h
        include/featherkit/util/input/sdlinputbackend.h)
    endif()

	if(${BUILD_SDL2BACKENDS})
		find_package(SDL2)
		if(SDL2_FOUND)
			include_directories(${SDL2_INCLUDE_DIR})
		elseif(SDK_PATH)
			link_directories(${SDK_PATH}/SDL-2.0/lib)
			include_directories(${SDK_PATH}/SDL-2.0/include)
		endif(SDL2_FOUND)
        set(ui_sdl2_backend_source_files
            src/util/window/sdl2windowbackend.cpp
            src/util/input/sdl2inputbackend.cpp)

        set(ui_sdl2_backend_header_files
            include/featherkit/util/window/sdl2windowbackend.h
            include/featherkit/util/input/sdl2inputbackend.h)
	endif()

    add_library(${project_name}-ui ${SHARED_OR_STATIC} ${glew_file} ${ui_header_files} ${ui_source_files} ${ui_util_source_files} ${ui_util_header_files} ${ui_sfml_backend_source_files} ${ui_sfml_backend_header_files} ${ui_sdl_backend_source_files} ${ui_sdl_backend_header_files} ${ui_sdl2_backend_source_files} ${ui_sdl2_backend_header_files})

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
    FILES README.md license.txt
    DESTINATION ${FEATHERKIT_MISC_DIR}
)
