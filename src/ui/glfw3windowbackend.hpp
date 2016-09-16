                                    // written by antonio trpeski //







#include<GLFW/glfw3.h>
#include "glfw3windowbackend.h"

namespace fea{

void glfw3WindowBackend::open(VideoMode mode, const std::string& title, uint32_t style, const ContextSettings& settings)
{
  glfwInit();
  window = glfwCreateWindow(mode.mwidth, mode.mheight, title.c_str(), NULL, NULL);
}

 void glfw3WindowBackend::close()
    {
        glfwDestroyWindow(window);
    }


    bool glfw3WindowBackend::isOpen() const
    {
        return window != nullptr;
    }

    const ContextSettings glfw3WindowBackend::getSettings() const
    {

        //  still looking on how to get and set context setings

    }

    Vec2I glfw3WindowBackend::getPosition() const
    {
        Vec2I s;
        s.x = 0;
        s.y = 0;

        if(isOpen())
            glfwGetWindowPos(window, &s.x , &s.y );

        return s;
    }

    void glfw3WindowBackend::setPosition(int32_t x, int32_t y)
    {
        if(isOpen())
        {
            glfwSetWindowPos(window , x , y);
        }
    }

    Vec2I glfw3WindowBackend::getSize() const
    {
        Vec2I s;
        s.x = 0;
        s.y = 0;

        if(isOpen())
            glfwGetWindowSize(window, &s.x, &s.y);

        return s;
    }

    void glfw3WindowBackend::setSize(int32_t w, int32_t h)
    {
        glfwSetWindowSize(window, w, h);
    }

    void glfw3WindowBackend::setTitle(const std::string& title)
    {
        glfwSetWindowTitle(window, title.c_str());
    }

    void glfw3WindowBackend::setIcon(uint32_t width, uint32_t height, const uint8_t* pixels)
    {
       glfwSetWindowIcon(window, 0 ,images ) 	
    }

    void glfw3WindowBackend::setVisible(bool visible)
    {
        // still working on it
    }

    void glfw3WindowBackend::setVSyncEnabled(bool enabled)
    {
        // still woriking on it
    }

    void glfw3WindowBackend::setMouseCursorVisible(bool visible)
    {
        // still working on it
    }

    void glfw3WindowBackend::setFramerateLimit(uint32_t limit)
    {
        //still woriking on it
    }

    bool glfw3WindowBackend::setRenderingActive(bool active) const
    {
        // still working on it
    }

    void glfw3WindowBackend::swapBuffers()
    {
        glfwSwapBuffers(window);
    }

    void glfw3WindowBackend::lockCursor(bool lock)
    {
        if(isOpen())
        {
            // still working on it
        }
    }

    glfw3WindowBackend::~glfw3WindowBackend()
    {
        close();
    }



}
