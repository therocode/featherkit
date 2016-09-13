                              // written by antonio trpeski  //








#ifndef GLFW3WINDOWBACKEND_H_INCLUDED
#define GLFW3WINDOWBACKEND_H_INCLUDED

namespace fea{
class glfw3WindowBackend
{
private:
    GLFWwindow *window;
public:
    void open(VideoMode mode, const std::string& title, uint32_t style, const ContextSettings& settings) const;
    void close();
    bool isOpen();
    void getSettings();
    Vec2I getPosition();
    void setPosition(int32_t x, int32_t y);
    vec2I getSize();
    void setSize(int32_t w, int32_t h);
    void setTitle(const std::string& title);
    void setIcon(uint32_t width, uint32_t height, const uint8_t* pixels);
    void setVisible(bool visible);
    void setVSyncEnabled(bool enabled);
    void setMouseCursorVisible(bool visible);
    void setFramerateLimit(uint32_t limit);
    bool setRenderingActive(bool active);
    void swapBuffers();
    void lockCursor(bool lock);
    ~glfw3WindowBackend();



};

}


#endif // GLFW3WINDOWBACKEND_H_INCLUDED
