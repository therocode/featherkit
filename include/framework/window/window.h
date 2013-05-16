#pragma once
#include <framework/window/videomode.h>
#include <framework/window/contextsettings.h>
#include <framework/window/windowstyle.h>
#include <framework/internal/intvec2.h>
#include <string>

namespace windbreeze
{
    class WindowBackend;

    class Window
    {
        public:
            Window(WindowBackend& backend) : windowBackend(backend) {}
            void create(VideoMode mode, const std::string& title, uint32_t style=Style::Default, const ContextSettings& settings=ContextSettings());
            void close();
            bool isOpen() const;
            const ContextSettings getSettings() const;

            IntVec2 getPosition() const;
            void setPosition(const IntVec2& position);
            IntVec2 getSize() const;
            void setSize (const IntVec2& size);
            void setTitle(const std::string& title);
            void setIcon(uint32_t width, uint32_t height, const uint8_t* pixels);
            void setVisible(bool visible);
            void setVSyncEnabled(bool enabled);
            void setMouseCursorVisible(bool visible);
            void setFramerateLimit(uint32_t limit);
            bool setRenderingActive(bool active=true) const;
            void display();


        private:
            WindowBackend& windowBackend;
    };
}
            /* hej this is from VidyaMöåd and should be here
            static VideoMode getDesktopMode();
            static const std::vector<VideoMode>& getFullscreenModes();
            bool isValid() const; */
