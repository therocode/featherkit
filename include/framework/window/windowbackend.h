#pragma once
#include <framework/window/videomode.h>
#include <framework/window/windowstyle.h>
#include <framework/window/contextsettings.h>
#include <framework/internal/intvec2.h>
#include <string>

namespace windbreeze
{
    class WindowBackend
    {
        public:
            virtual void create(VideoMode mode, const std::string& title, uint32_t style=Style::Default, const ContextSettings& settings=ContextSettings()) = 0;
            virtual void close() = 0;
            virtual bool isOpen() const = 0;

            virtual const ContextSettings getSettings() const = 0;
            virtual IntVec2 getPosition() const = 0;
            virtual void setPosition(const IntVec2& position) = 0;
            virtual IntVec2 getSize() const = 0;
            virtual void setSize (const IntVec2& size) = 0;
            virtual void setTitle(const std::string& title) = 0;
            virtual void setIcon(uint32_t width, uint32_t height, const uint8_t* pixels) = 0;
            virtual void setVisible(bool visible) = 0;
            virtual void setVSyncEnabled(bool enabled) = 0;
            virtual void setMouseCursorVisible(bool visible) = 0;
            virtual void setFramerateLimit(uint32_t limit) = 0;
            virtual bool setRenderingActive(bool active=true) const = 0;
            virtual void display() = 0;
    };
}
