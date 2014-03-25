#cmake ver req
cmake_minimum_required(VERSION 2.8.3)

if(NOT CMAKE_BUILD_TYPE )
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Select if you want to build Debug or Release" FORCE )
endif()

#project name
set(project_name featherkit)
project(${project_name})

set(SHARED_BUILD TRUE CACHE BOOL "Set this to false if you want a static build")

set(BUILD_AUDIO TRUE CACHE BOOL "Selects if the audio module should be built")
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

SET(CMAKE_DEBUG_POSTFIX "-d")

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

if(BUILD_AUDIO)
    ##Audio module##

    find_package(OpenAL REQUIRED)
    if(OPENAL_FOUND)
        include_directories(${OPENAL_INCLUDE_DIR})
    endif()

    find_package(SndFile REQUIRED)
    if(SNDFILE_FOUND)
        include_directories(${SNDFILE_INCLUDE_DIRS})
    endif()

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-audio)

    set(audio_source_files 
        src/audio/audio.cpp
        src/audio/audiobase.cpp
        src/audio/audiobuffer.cpp
        src/audio/audiodata.cpp
        src/audio/audioeffect.cpp
        src/audio/audiofile.cpp
        src/audio/audiofilestream.cpp
        src/audio/audiofilter.cpp
        src/audio/audioplayer.cpp
        src/audio/audiosample.cpp
        src/audio/audiostream.cpp
        src/audio/effectslot.cpp
        src/audio/audiofilenotfoundexception.cpp
        src/audio/listener.cpp
        src/audio/playsource.cpp
        src/audio/oscillator.cpp
        src/audio/efx/chorus.cpp
        src/audio/efx/compressor.cpp
        src/audio/efx/distortion.cpp
        src/audio/efx/echo.cpp
        src/audio/efx/equalizer.cpp
        src/audio/efx/flanger.cpp
        src/audio/efx/lowpassfilter.cpp
        src/audio/efx/reverb.cpp
        src/audio/efx/ringmodulator.cpp)

    set(audio_header_files
        include/featherkit/audio/audio.hpp
        include/featherkit/audio/audiobase.hpp
        include/featherkit/audio/audiobuffer.hpp
        include/featherkit/audio/audiodata.hpp
        include/featherkit/audio/audioeffect.hpp
        include/featherkit/audio/audiofile.hpp
        include/featherkit/audio/audiofilestream.hpp
        include/featherkit/audio/audiofilter.hpp
        include/featherkit/audio/audioplayer.hpp
        include/featherkit/audio/audiosample.hpp
        include/featherkit/audio/audiostream.hpp
        include/featherkit/audio/effectslot.hpp
        include/featherkit/audio/audiofilenotfoundexception.hpp
        include/featherkit/audio/listener.hpp
        include/featherkit/audio/playsource.hpp
        include/featherkit/audio/oscillator.hpp
        include/featherkit/audio/efx/chorus.hpp
        include/featherkit/audio/efx/compressor.hpp
        include/featherkit/audio/efx/distortion.hpp
        include/featherkit/audio/efx/echo.hpp
        include/featherkit/audio/efx/equalizer.hpp
        include/featherkit/audio/efx/flanger.hpp
        include/featherkit/audio/efx/lowpassfilter.hpp
        include/featherkit/audio/efx/reverb.hpp
        include/featherkit/audio/efx/ringmodulator.hpp)

    add_library(${project_name}-audio ${SHARED_OR_STATIC} ${audio_header_files} ${audio_source_files})
    target_link_libraries(${project_name}-audio ${OPENAL_LIBRARY} ${SNDFILE_LIBRARIES})
endif()

if(BUILD_STRUCTURE)
    ##Structure module##

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-structure)

    set(structure_source_files 
        src/structure/application.cpp
        src/structure/gamestatemachine.cpp)

    set(structure_header_files include/featherkit/structure/application.hpp
        include/featherkit/structure/gamestate.hpp
        include/featherkit/structure/gamestatemachine.hpp
        include/featherkit/util/loosentree.hpp
        include/featherkit/util/loosentree.inl)

    add_library(${project_name}-structure ${SHARED_OR_STATIC} ${structure_header_files} ${structure_source_files})
endif()

if(BUILD_ENTITY)
    ##Entity module##

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-entity)

    set(entity_source_files
        src/entity/entity.cpp
        src/entity/entitycomponent.cpp
        src/entity/entityfactory.cpp
        src/entity/filenotfoundexception.cpp
        src/entity/entitystorage.cpp
        src/entity/entitymanager.cpp)

    set(entity_header_files 
        include/featherkit/entity/entity.hpp
        include/featherkit/entity/entity.inl
        include/featherkit/entity/entityfactory.hpp
        include/featherkit/entity/entityfactory.inl
        include/featherkit/entity/filenotfoundexception.hpp
        include/featherkit/entity/entitycomponent.hpp
        include/featherkit/entity/entitymanager.hpp
        include/featherkit/entity/entitymanager.inl
        include/featherkit/entity/entitystorage.hpp
        include/featherkit/entity/entitystorage.inl
        include/featherkit/entity/entitytemplate.hpp)

    set(entity_util_source_files
        src/util/entity/basictypeadder.cpp
        src/util/entity/glmtypeadder.cpp
        src/util/entity/jsonentityloader.cpp)
    set(entity_util_header_files
        include/featherkit/util/entity/basictypeadder.hpp
        include/featherkit/util/entity/glmtypeadder.hpp
        include/featherkit/util/entity/jsonentityloader.hpp)

    add_library(${project_name}-entity ${SHARED_OR_STATIC} ${entity_header_files} ${entity_source_files} ${entity_util_source_files} ${entity_util_header_files})
endif()

if(BUILD_MESSAGING)
    ##Messaging module##

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-messaging)

    set(messaging_source_files 
        src/messaging/messagebus.cpp)

    set(messaging_header_files 
        include/featherkit/messaging/messagebus.hpp
        include/featherkit/messaging/messagebus.inl
        include/featherkit/messaging/message.hpp
        include/featherkit/messaging/message.inl
        include/featherkit/messaging/messagereceiver.hpp)
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
        src/rendering/color.cpp
        src/rendering/defaultshader.cpp
        src/rendering/drawable2d.cpp
        src/rendering/gl_core_3_2.c
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
        include/featherkit/rendering/animatedquad.hpp
        include/featherkit/rendering/animation.hpp
        include/featherkit/rendering/camera.hpp
        include/featherkit/rendering/color.hpp
        include/featherkit/rendering/defaultshader.hpp
        include/featherkit/rendering/drawable2d.hpp
        include/featherkit/rendering/gl_core_3_2.h
        include/featherkit/rendering/opengl.hpp
        include/featherkit/rendering/projection.hpp
        include/featherkit/rendering/quad.hpp
        include/featherkit/rendering/renderer2d.hpp
        include/featherkit/rendering/renderinfo.hpp
        include/featherkit/rendering/rendertarget.hpp
        include/featherkit/rendering/repeatedquad.hpp
        include/featherkit/rendering/shader.hpp
        include/featherkit/rendering/subrectquad.hpp
        include/featherkit/rendering/texture.hpp
        include/featherkit/rendering/tilechunk.hpp
        include/featherkit/rendering/tilemap.hpp
        include/featherkit/rendering/uniform.hpp
        include/featherkit/rendering/vertexattribute.hpp
        include/featherkit/rendering/viewport.hpp)

    if(BUILD_RENDERING_TEXT)
        set(freetype-gl_source_files 
            src/freetype-gl/platform.c
            src/freetype-gl/texture-atlas.c
            src/freetype-gl/texture-font.c
            src/freetype-gl/vector.c)

        set(rendering_source_files ${rendering_source_files}
            src/rendering/textsurface.cpp
            src/rendering/font.cpp)

        set(rendering_header_files ${rendering_header_files}
            include/featherkit/rendering/textsurface.hpp
            include/featherkit/rendering/font.hpp
            include/featherkit/rendering/font.inl)

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

    add_library(${project_name}-rendering ${SHARED_OR_STATIC} ${rendering_source_files} ${rendering_header_files} ${freetype-gl_source_files} ${freetype-gl_header_files})

    if(BUILD_RENDERING_TEXT)
        FIND_PACKAGE( Freetype REQUIRED )
        include_directories(${FREETYPE_INCLUDE_DIRS})
    endif(BUILD_RENDERING_TEXT)

    target_link_libraries(${project_name}-rendering ${FREETYPE_LIBRARY} ${OPENGL_LIBRARIES})

endif()

if(BUILD_UI)
    ##UI module##

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-ui)

    #find all source files
    set(ui_source_files 
        src/ui/actiontrigger.cpp
        src/ui/inputhandler.cpp
        src/ui/inputfilenotfoundexception.cpp
        src/ui/contextsettings.cpp
        src/ui/videomode.cpp
        src/ui/window.cpp)

    set(ui_header_files 
        include/featherkit/ui/contextsettings.hpp
        include/featherkit/ui/vec2i.hpp
        include/featherkit/ui/videomode.hpp
        include/featherkit/ui/windowbackend.hpp
        include/featherkit/ui/window.hpp
        include/featherkit/ui/windowstyle.hpp
        include/featherkit/ui/actionhandler.hpp
        include/featherkit/ui/actionhandler.inl
        include/featherkit/ui/actiontrigger.hpp
        include/featherkit/ui/event.hpp
        include/featherkit/ui/gamepad.hpp
        include/featherkit/ui/inputbackend.hpp
        include/featherkit/ui/inputfilenotfoundexception.hpp
        include/featherkit/ui/inputhandler.hpp
        include/featherkit/ui/keyboard.hpp
        include/featherkit/ui/mouse.hpp)

    set(ui_util_header_files 
        include/featherkit/util/ui/jsonactioniohandler.hpp
        include/featherkit/util/ui/jsonactioniohandler.inl)

    if(${BUILD_SFMLBACKENDS})
        set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-sfml)

        find_package(SFML 2.0 COMPONENTS system window REQUIRED)
        if(SFML_FOUND)
            include_directories(${SFML_INCLUDE_DIR})
        endif(SFML_FOUND)
        set(ui_sfml_backend_source_files 
            src/ui/sfmlwindowbackend.cpp
            src/ui/sfmlinputbackend.cpp)

        set(ui_sfml_backend_header_files
            include/featherkit/ui/sfmlwindowbackend.hpp
            include/featherkit/ui/sfmlinputbackend.hpp)

        add_library(${project_name}-sfml ${SHARED_OR_STATIC} ${ui_sfml_backend_source_files} ${ui_sfml_backend_header_files})
        target_link_libraries(${project_name}-sfml ${SFML_LIBRARIES})
    endif()

    if(${BUILD_SDLBACKENDS})
        set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-sdl)

        find_package(SDL REQUIRED)
        if(SDL_FOUND)
            include_directories(${SDL_INCLUDE_DIR})
        endif(SDL_FOUND)
        set(ui_sdl_backend_source_files 
            src/ui/sdlwindowbackend.cpp
            src/ui/sdlinputbackend.cpp)

        set(ui_sdl_backend_header_files
        include/featherkit/ui/sdlwindowbackend.hpp
        include/featherkit/ui/sdlinputbackend.hpp)

        add_library(${project_name}-sdl ${SHARED_OR_STATIC} ${ui_sdl_backend_source_files} ${ui_sdl_backend_header_files})
        target_link_libraries(${project_name}-sdl ${SDL_LIBRARY})
    endif()

	if(${BUILD_SDL2BACKENDS})
        set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-sdl2)

		find_package(SDL2)
		if(SDL2_FOUND)
			include_directories(${SDL2_INCLUDE_DIR})
		elseif(SDK_PATH)
			link_directories(${SDK_PATH}/SDL-2.0/lib)
			include_directories(${SDK_PATH}/SDL-2.0/include)
		endif(SDL2_FOUND)
        set(ui_sdl2_backend_source_files
            src/ui/sdl2windowbackend.cpp
            src/ui/sdl2inputbackend.cpp)

        set(ui_sdl2_backend_header_files
            include/featherkit/ui/sdl2windowbackend.hpp
            include/featherkit/ui/sdl2inputbackend.hpp)
    
        add_library(${project_name}-sdl2 ${SHARED_OR_STATIC} ${ui_sdl2_backend_source_files} ${ui_sdl2_backend_header_files})
		target_link_libraries(${project_name}-sdl2 ${SDL2_LIBRARY})
	endif()

    add_library(${project_name}-ui ${SHARED_OR_STATIC} ${ui_header_files} ${ui_source_files} ${ui_util_source_files} ${ui_util_header_files})

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
