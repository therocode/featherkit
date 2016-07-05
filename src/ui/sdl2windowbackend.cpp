#include <fea/ui/sdl2windowbackend.hpp>
#include <iostream>

namespace fea
{
    SDL2WindowBackend::SDL2WindowBackend() : mWindow(nullptr)
    {
        SDL_Init(SDL_INIT_VIDEO);
    }

    void SDL2WindowBackend::open(VideoMode mode, const std::string& title, uint32_t style, const ContextSettings& settings)
    {
        //todo: fix style
        (void) style;
        (void) settings;
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, settings.mMajorVersion);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, settings.mMinorVersion);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, settings.mType == ContextSettings::Type::CORE ? SDL_GL_CONTEXT_PROFILE_CORE : SDL_GL_CONTEXT_PROFILE_ES);
        mWindow = SDL_CreateWindow(title.c_str(),
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                mode.mWidth, mode.mHeight,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        std::cout << SDL_GetError() << "\n";
        mGlContext = SDL_GL_CreateContext(mWindow);
        std::cout << SDL_GetError() << "\n";

    }

    void SDL2WindowBackend::close()
    {
        SDL_GL_DeleteContext(mGlContext);
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
        mWindow = nullptr;
    }


    bool SDL2WindowBackend::isOpen() const
    {
        return mWindow != nullptr;
    }

    const ContextSettings SDL2WindowBackend::getSettings() const
    {
        //settings not finalized;
        return ContextSettings();
    }

    Vec2I SDL2WindowBackend::getPosition() const
    {
        Vec2I s;
        s.x = 0;
        s.y = 0;

        if(isOpen())
            SDL_GetWindowPosition(mWindow, &s.x, &s.y);

        return s;
    }

    void SDL2WindowBackend::setPosition(int32_t x, int32_t y)
    {
        if(isOpen())
        {
            SDL_SetWindowPosition(mWindow, x, y);
        }
    }

    Vec2I SDL2WindowBackend::getSize() const
    {
        Vec2I s;
        s.x = 0;
        s.y = 0;

        if(isOpen())
            SDL_GetWindowSize(mWindow, &s.x, &s.y);

        return s;
    }

    void SDL2WindowBackend::setSize(int32_t w, int32_t h)
    {
        SDL_SetWindowSize(mWindow, w, h);
    }

    void SDL2WindowBackend::setTitle(const std::string& title)
    {
        SDL_SetWindowTitle(mWindow, title.c_str());
    }

    void SDL2WindowBackend::setIcon(uint32_t width, uint32_t height, const uint8_t* pixels)
    {
        SDL_Surface* f = SDL_CreateRGBSurfaceFrom((void*)pixels, width, height, 32, width*4, 0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
        if(f == NULL){
            printf("Window icon could not be loaded: %s\n", SDL_GetError());
            //return;
        }
        SDL_SetWindowIcon(mWindow, f);
    }

    void SDL2WindowBackend::setVisible(bool visible)
    {
        //should be fixed
        (void) visible;
    }

    void SDL2WindowBackend::setVSyncEnabled(bool enabled)
    {
        SDL_GL_SetSwapInterval(enabled?1:0);
    }

    void SDL2WindowBackend::setMouseCursorVisible(bool visible)
    {
        //should be fixed
        (void)visible;
    }

    void SDL2WindowBackend::setFramerateLimit(uint32_t limit)
    {
        //should be fixed
        (void)limit;
    }

    bool SDL2WindowBackend::setRenderingActive(bool active) const
    {
        //should be fixed
        (void)active;
        return true;
    }

    void SDL2WindowBackend::swapBuffers()
    {
        SDL_GL_SwapWindow(mWindow);
    }

    void SDL2WindowBackend::lockCursor(bool lock)
    {
        if(isOpen())
        {
            SDL_SetRelativeMouseMode((SDL_bool)lock);
            SDL_SetWindowGrab(mWindow, (SDL_bool)lock);
        }
    }

    SDL2WindowBackend::~SDL2WindowBackend()
    {
        close();
        //free(mWindow);
    }
}
