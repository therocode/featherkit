#pragma once
#include <fea/config.hpp>
#include <fea/ui/windowbackend.hpp>

namespace fea{
class GLFW3WindowBackend : public WindowBackend
{
private:
    GLFWwindow *window;
    GLFWimage *images[2];
public:
    void open(VideoMode mode, const std::string& title, uint32_t style, const ContextSettings& settings) override;
    void close();
    bool isOpen() const;
    const ContextSettings getSettings() const override; //not supported
    Vec2I getPosition() const;
    void setPosition(int32_t x, int32_t y);
    Vec2I getSize() const;
    void setSize(int32_t w, int32_t h);
    void setTitle(const std::string& title);
    void setIcon(uint32_t width, uint32_t height, const uint8_t* pixels);
    void setVisible(bool visible);
    void setVSyncEnabled(bool enabled);
    void setMouseCursorVisible(bool visible);
    void setFramerateLimit(uint32_t limit);
    bool setRenderingActive(bool active) const override;
    void swapBuffers();
    void lockCursor(bool lock);
    ~GLFW3WindowBackend();



};

}
