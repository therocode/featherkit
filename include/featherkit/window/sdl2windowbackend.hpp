#pragma once
//#define NO_SDL_GLEXT
#include <featherkit/window/windowbackend.hpp>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_opengl.hpp>
#include <memory>

namespace fea
{
    class SDL2WindowBackend : public WindowBackend
    {
        public:
            SDL2WindowBackend();

            void create(VideoMode mode, const std::string& title, uint32_t style = Style::Default, const ContextSettings& settings = ContextSettings()) override; //style and settings not supported
            void close() override;
            bool isOpen() const override;
            const ContextSettings getSettings() const override; //not supported
            Vec2I getPosition() const override;
            void setPosition(int32_t x, int32_t y) override;
            Vec2I getSize() const override;
            void setSize(int32_t w, int32_t h) override;
            void setTitle(const std::string& title) override;
            void setIcon(uint32_t width, uint32_t height, const uint8_t* pixels) override;
            void setVisible(bool visible) override; //not supported
            void setVSyncEnabled(bool enabled) override;
            void setMouseCursorVisible(bool visible) override; //not supported
            void setFramerateLimit(uint32_t limit) override; //not supported

            bool setRenderingActive(bool active = true) const override; //not supported
            void swapBuffers() override;
            void lockCursor(bool lock) override;
            ~SDL2WindowBackend();
        private:
            SDL_Window* mWindow;
            SDL_GLContext mGlContext;
    };
}
