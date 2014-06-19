#cmake ver req
cmake_minimum_required(VERSION 2.8.3)

if(NOT CMAKE_BUILD_TYPE )
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Select if you want to build Debug or Release" FORCE )
endif()

#project name
set(project_name fea)
project(${project_name})

set(SHARED_BUILD TRUE CACHE BOOL "Set this to false if you want a static build")

set(BUILD_AUDIO TRUE CACHE BOOL "Selects if the audio module should be built")
set(BUILD_STRUCTURE TRUE CACHE BOOL "Selects if the structure module should be built")
set(BUILD_ENTITY TRUE CACHE BOOL "Selects if the entity module should be built")
set(BUILD_MESSAGING TRUE CACHE BOOL "Selects if the messaging module should be built")
set(BUILD_RENDERING TRUE CACHE BOOL "Selects if the rendering module should be built")
set(BUILD_UI TRUE CACHE BOOL "Selects if the UI module should be built")
set(BUILD_UTIL TRUE CACHE BOOL "Selects if the util module should be built")

set(BUILD_SFMLBACKENDS FALSE CACHE BOOL "Selects if the SFML backends should be built")
set(BUILD_SDLBACKENDS FALSE CACHE BOOL "Selects if the SDL backends should be built")
set(BUILD_SDL2BACKENDS FALSE CACHE BOOL "Selects if the SDL2 backends should be built")

set(BUILD_JSON TRUE CACHE BOOL "Selects if the json (de)serialization functions should be built")

set(SDK_PATH "" CACHE PATH "Optional path to the Featherkit SDK. If this is not set, the dependencies have to be handled manually.")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  #for shared libs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  #for static libs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  #for static libs

SET(CMAKE_DEBUG_POSTFIX "-d")

if(SHARED_BUILD)
    set(SHARED_OR_STATIC SHARED)
    add_definitions(-DFEA_SHARED=1)
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



set(64BIT_ASM_OPTIMISATIONS FALSE CACHE BOOL "use assembler optimisation for noise generation. only compatible with 64 bit builds")
set(ASM_COMPILER_PATH "" CACHE FILEPATH "select asm compiler to use (nasm/yasm)")
if(64BIT_ASM_OPTIMISATIONS) #if this option is chosen, then it #ifdef NOISE_ASM in the code will be run
	set(YASM_PATH ${ASM_COMPILER_PATH})
	enable_language(ASM-NASM)
	add_definitions(-DNOISE_ASM)
endif(64BIT_ASM_OPTIMISATIONS)



if(NOT MSVC)
    set(CPP_11_FLAG -std=c++11)
endif()

#if(MINGW OR CMAKE_COMPILER_IS_GNUCXX OR Clang)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wshadow -Wconversion -Wno-long-long -pedantic -Wconstant-conversion")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPP_11_FLAG}")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
#endif()

add_definitions(-DFEA_EXPORT=1)

if(BUILD_JSON)
    find_package(JsonCpp REQUIRED)
    if(JSONCPP_FOUND)
        include_directories(${JSONCPP_INCLUDE_DIRS})
        add_definitions(-DUSE_JSONCPP)
    endif()
endif()

if(BUILD_AUDIO)
    ##Audio module##
    set(DISABLE_EFX FALSE CACHE BOOL "Set to true to disable the OpenAL EFX extension. Useful for some systems")

    if(DISABLE_EFX)
        add_definitions(-DFEA_NO_EFX)
    endif()

    if(NOT EMSCRIPTEN)
        find_package(OpenAL REQUIRED)
        if(OPENAL_FOUND)
            include_directories(${OPENAL_INCLUDE_DIR})
        endif()
    endif()

    find_package(VorbisFile REQUIRED)
    if(VorbisFile_FOUND)
        include_directories(${VorbisFile_INCLUDE_DIR})
    endif()

    find_package(OGG REQUIRED)
    if(OGG_FOUND)
        include_directories(${OGG_INCLUDE_DIR})
    endif()

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-audio)

    set(audio_source_files 
        src/audio/audio.cpp
        src/audio/audiobase.cpp
        src/audio/audiobuffer.cpp
        src/audio/audiofile.cpp
        src/audio/audiofilestream.cpp
        src/audio/audioplayer.cpp
        src/audio/audiosample.cpp
        src/audio/audiostream.cpp
        src/audio/audiofilenotfoundexception.cpp
        src/audio/listener.cpp
        src/audio/playsource.cpp
        src/audio/oscillator.cpp)

    set(audio_header_files
        include/fea/audio/openal.hpp
        include/fea/audio/audio.hpp
        include/fea/audio/audiobase.hpp
        include/fea/audio/audiobuffer.hpp
        include/fea/audio/audiofile.hpp
        include/fea/audio/audiofilestream.hpp
        include/fea/audio/audioplayer.hpp
        include/fea/audio/audiosample.hpp
        include/fea/audio/audiostream.hpp
        include/fea/audio/audiofilenotfoundexception.hpp
        include/fea/audio/listener.hpp
        include/fea/audio/playsource.hpp
        include/fea/audio/oscillator.hpp)

    if(NOT EMSCRIPTEN)
        set(audio_efx_source_files 
            src/audio/audioeffect.cpp
            src/audio/audiofilter.cpp
            src/audio/effectslot.cpp
            src/audio/efx/chorus.cpp
            src/audio/efx/compressor.cpp
            src/audio/efx/distortion.cpp
            src/audio/efx/echo.cpp
            src/audio/efx/equalizer.cpp
            src/audio/efx/flanger.cpp
            src/audio/efx/lowpassfilter.cpp
            src/audio/efx/presets.cpp
            src/audio/efx/reverb.cpp
            src/audio/efx/ringmodulator.cpp)

        set(audio_efx_header_files
            include/fea/audio/audioeffect.hpp
            include/fea/audio/audiofilter.hpp
            include/fea/audio/effectslot.hpp
            include/fea/audio/efx/chorus.hpp
            include/fea/audio/efx/compressor.hpp
            include/fea/audio/efx/distortion.hpp
            include/fea/audio/efx/echo.hpp
            include/fea/audio/efx/equalizer.hpp
            include/fea/audio/efx/flanger.hpp
            include/fea/audio/efx/lowpassfilter.hpp
            include/fea/audio/efx/presets.hpp
            include/fea/audio/efx/reverb.hpp
            include/fea/audio/efx/ringmodulator.hpp)
    endif()

    add_library(${project_name}-audio ${SHARED_OR_STATIC}
        ${audio_source_files}
        ${audio_header_files}
        ${audio_efx_source_files}
        ${audio_efx_header_files})

    target_link_libraries(${project_name}-audio ${OPENAL_LIBRARY} ${VorbisFile_LIBRARIES} ${OGG_LIBRARIES})
endif()

if(BUILD_STRUCTURE)
    ##Structure module##

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-structure)

    set(structure_source_files 
        src/structure/application.cpp
        src/structure/gamestatemachine.cpp)

    set(structure_header_files include/fea/structure/application.hpp
        include/fea/structure/gamestate.hpp
        include/fea/structure/gamestatemachine.hpp)

    add_library(${project_name}-structure ${SHARED_OR_STATIC}
        ${structure_source_files}
        ${structure_header_files})
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
        src/entity/entitymanager.cpp
        src/entity/basictypeadder.cpp
        src/entity/glmtypeadder.cpp)

    set(entity_header_files
        include/fea/entity/entity.hpp
        include/fea/entity/entity.inl
        include/fea/entity/entityfactory.hpp
        include/fea/entity/entityfactory.inl
        include/fea/entity/filenotfoundexception.hpp
        include/fea/entity/entitycomponent.hpp
        include/fea/entity/entitymanager.hpp
        include/fea/entity/entitymanager.inl
        include/fea/entity/entitystorage.hpp
        include/fea/entity/entitystorage.inl
        include/fea/entity/entitytemplate.hpp
        include/fea/entity/basictypeadder.hpp
        include/fea/entity/glmtypeadder.hpp)

    if(BUILD_JSON)
        set(entity_json_source_files
            src/entity/jsonentityloader.cpp)

        set(entity_json_header_files
            include/fea/entity/jsonentityloader.hpp)
    endif()

    add_library(${project_name}-entity ${SHARED_OR_STATIC}
        ${entity_source_files}
        ${entity_header_files}
        ${entity_json_source_files}
        ${entity_json_header_files})

    target_link_libraries(${project_name}-entity ${JSONCPP_LIBRARIES})
endif()

if(BUILD_MESSAGING)
    ##Messaging module##

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-messaging)

    set(messaging_source_files 
        src/messaging/messagebus.cpp)

    set(messaging_header_files 
        include/fea/messaging/messagebus.hpp
        include/fea/messaging/messagebus.inl
        include/fea/messaging/messagereceiver.hpp)

    add_library(${project_name}-messaging ${SHARED_OR_STATIC}
        ${messaging_source_files}
        ${messaging_header_files})
endif()

if(BUILD_RENDERING)
    set(BUILD_RENDERING_TEXT TRUE CACHE BOOL "Selects if text rendering should be built (requires freetype2)")
    ##Rendering module##

    find_package(GLM REQUIRED)
    if(GLM_FOUND)
        include_directories(${WINFIX} ${GLM_INCLUDE_DIRS})
    endif()

    if(NOT EMSCRIPTEN)
        find_package(OpenGL REQUIRED)
        if(OPENGL_FOUND)
            include_directories(${OPENGL_INCLUDE_DIRS})
        endif(OPENGL_FOUND)
    endif()

    if(BUILD_RENDERING_TEXT)
        FIND_PACKAGE( Freetype REQUIRED )
        include_directories(${FREETYPE_INCLUDE_DIRS})
    endif(BUILD_RENDERING_TEXT)

    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-rendering)

    set(rendering_source_files 
        src/rendering/animatedquad.cpp
        src/rendering/animation.cpp
        src/rendering/camera.cpp
        src/rendering/color.cpp
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
        include/fea/rendering/animatedquad.hpp
        include/fea/rendering/animation.hpp
        include/fea/rendering/camera.hpp
        include/fea/rendering/color.hpp
        include/fea/rendering/defaultshader.hpp
        include/fea/rendering/drawable2d.hpp
        include/fea/rendering/gl_core_3_2.h
        include/fea/rendering/glmhash.hpp
        include/fea/rendering/opengl.hpp
        include/fea/rendering/projection.hpp
        include/fea/rendering/quad.hpp
        include/fea/rendering/renderer2d.hpp
        include/fea/rendering/renderentity.hpp
        include/fea/rendering/rendertarget.hpp
        include/fea/rendering/repeatedquad.hpp
        include/fea/rendering/shader.hpp
        include/fea/rendering/subrectquad.hpp
        include/fea/rendering/texture.hpp
        include/fea/rendering/tilechunk.hpp
        include/fea/rendering/tilemap.hpp
        include/fea/rendering/uniform.hpp
        include/fea/rendering/vertexattribute.hpp
        include/fea/rendering/viewport.hpp)

    if(NOT EMSCRIPTEN)
        set(rendering_gl_core_source_files
            src/rendering/gl_core_3_2.c)
    endif()

    if(BUILD_RENDERING_TEXT)
        set(freetype_gl_source_files 
            src/freetype-gl/platform.c
            src/freetype-gl/texture-atlas.c
            src/freetype-gl/texture-font.c
            src/freetype-gl/vector.c)

        set(freetype_gl_header_files 
            include/fea/freetype-gl/platform.h
            include/fea/freetype-gl/texture-atlas.h
            include/fea/freetype-gl/texture-font.h
            include/fea/freetype-gl/vec234.h
            include/fea/freetype-gl/vector.h)

        set(rendering_text_source_files
            src/rendering/textsurface.cpp
            src/rendering/font.cpp)

        set(rendering_text_header_files
            include/fea/rendering/textsurface.hpp
            include/fea/rendering/font.hpp
            include/fea/rendering/font.inl)
    endif(BUILD_RENDERING_TEXT)

    add_library(${project_name}-rendering ${SHARED_OR_STATIC}
        ${rendering_source_files}
        ${rendering_header_files}
        ${rendering_gl_core_source_files}
        ${freetype_gl_source_files}
        ${freetype_gl_header_files}
        ${rendering_text_source_files}
        ${rendering_text_header_files})

    target_link_libraries(${project_name}-rendering ${OPENGL_LIBRARIES} ${FREETYPE_LIBRARY})
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
        #include/fea/ui/contextsettings.hpp
        include/fea/ui/vec2i.hpp
        include/fea/ui/videomode.hpp
        include/fea/ui/windowbackend.hpp
        include/fea/ui/window.hpp
        include/fea/ui/windowstyle.hpp
        include/fea/ui/actionhandler.hpp
        include/fea/ui/actionhandler.inl
        include/fea/ui/actiontrigger.hpp
        include/fea/ui/event.hpp
        include/fea/ui/gamepad.hpp
        include/fea/ui/inputbackend.hpp
        include/fea/ui/inputfilenotfoundexception.hpp
        include/fea/ui/inputhandler.hpp
        include/fea/ui/keyboard.hpp
        include/fea/ui/mouse.hpp)

    if(BUILD_JSON)
        set(ui_json_header_files 
            include/fea/ui/jsonactioniohandler.hpp
            include/fea/ui/jsonactioniohandler.inl)
    endif()
    
    add_library(${project_name}-ui ${SHARED_OR_STATIC}
        ${ui_header_files}
        ${ui_source_files}
        ${ui_json_header_files})

    target_link_libraries(${project_name}-ui ${JSONCPP_LIBRARIES})

    if(${BUILD_SFMLBACKENDS})
        find_package(SFML 2.0 COMPONENTS system window REQUIRED)
        if(SFML_FOUND)
            include_directories(${SFML_INCLUDE_DIR})
        endif(SFML_FOUND)

        set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-sfml)

        set(ui_sfml_backend_source_files 
            src/ui/sfmlwindowbackend.cpp
            #src/ui/contextsettings.cpp
            src/ui/sfmlinputbackend.cpp)

        set(ui_sfml_backend_header_files
            include/fea/ui/sfmlwindowbackend.hpp
            include/fea/ui/sfmlinputbackend.hpp)

        add_library(${project_name}-sfml ${SHARED_OR_STATIC}
            ${ui_sfml_backend_source_files}
            ${ui_sfml_backend_header_files})

        target_link_libraries(${project_name}-sfml ${SFML_LIBRARIES} ${project_name}-ui)
    endif()

    if(${BUILD_SDLBACKENDS})
        set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-sdl)

        if(NOT EMSCRIPTEN)
            find_package(SDL REQUIRED)
            if(SDL_FOUND)
                include_directories(${SDL_INCLUDE_DIR})
            endif(SDL_FOUND)
        endif()

        set(ui_sdl_backend_source_files 
            src/ui/sdlwindowbackend.cpp
            #src/ui/contextsettings.cpp
            src/ui/sdlinputbackend.cpp)

        set(ui_sdl_backend_header_files
        include/fea/ui/sdlwindowbackend.hpp
        include/fea/ui/sdlinputbackend.hpp)

        add_library(${project_name}-sdl ${SHARED_OR_STATIC}
            ${ui_sdl_backend_source_files}
            ${ui_sdl_backend_header_files})

        target_link_libraries(${project_name}-sdl ${SDL_LIBRARY} ${project_name}-ui)
    endif()

    if(${BUILD_SDL2BACKENDS})
        find_package(SDL2 REQUIRED)
        if(SDL2_FOUND)
            include_directories(${SDL2_INCLUDE_DIR})
        elseif(SDK_PATH)
            link_directories(${SDK_PATH}/SDL-2.0/lib)
            include_directories(${SDK_PATH}/SDL-2.0/include)
        endif(SDL2_FOUND)

        set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-sdl2)

        set(ui_sdl2_backend_source_files
            src/ui/sdl2windowbackend.cpp
            #src/ui/contextsettings.cpp
            src/ui/sdl2inputbackend.cpp)

        set(ui_sdl2_backend_header_files
            include/fea/ui/sdl2windowbackend.hpp
            include/fea/ui/sdl2inputbackend.hpp)
    
        add_library(${project_name}-sdl2 ${SHARED_OR_STATIC} ${ui_sdl2_backend_source_files} ${ui_sdl2_backend_header_files})
        target_link_libraries(${project_name}-sdl2 ${SDL2_LIBRARY} ${project_name}-ui)
    endif()
endif()

if(BUILD_UTIL)
    ##Util module##
    
    set(BUILT_TARGETS ${BUILT_TARGETS} ${project_name}-util)
    
    #find all source files
    set(util_source_files
        src/util/noise.cpp
        src/util/simplexnoise.cpp
        src/util/voronoinoise.cpp
        src/util/whitenoise.cpp
		src/util/asmnoise.asm)
    
    set(util_header_files 
        include/fea/util/loosentree.hpp
        include/fea/util/loosentree.inl
        include/fea/util/pathfinder.hpp
        include/fea/util/pathfinder.inl
        include/fea/util/noise.hpp
        include/fea/util/simplexnoise.hpp
        include/fea/util/voronoinoise.hpp
        include/fea/util/whitenoise.hpp
        include/fea/util/asmnoise.hpp)
    
    add_library(${project_name}-util ${SHARED_OR_STATIC}
        ${util_header_files}
        ${util_source_files})
    
    target_link_libraries(${project_name}-util)
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
