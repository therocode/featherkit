#include<GLFW/glfw3.h>
#include <fea/ui/glfw3windowbackend.hpp>

namespace fea{
    
     int key_press(KeyBoard::Code pkey_code ,bool psystem,bool pcontrol,bool pshift,bool palt )
+    {
+        KeyEvent Event;
+        Event.code =pKey_code;
+        Event.shift = pshift;
+        Event.control = pcontrol;
+        Event.alt = palt;
+        Event.system = psystem;
+        
+        return Event;
+    }

    void GLFW3WindowBackend::open(VideoMode mode, const std::string& title, uint32_t style, const ContextSettings& settings)
    {
        glfwInit();
        window = glfwCreateWindow(mode.mWidth, mode.mHeight, title.c_str(), NULL, NULL);
    }

    void GLFW3WindowBackend::close()
    {
        glfwDestroyWindow(window);
    }


    bool GLFW3WindowBackend::isOpen() const
    {
        return window != nullptr;
    }

    const ContextSettings GLFW3WindowBackend::getSettings() const
    {

        //  still looking on how to get and set context setings

    }

    Vec2I GLFW3WindowBackend::getPosition() const
    {
        Vec2I s;
        s.x = 0;
        s.y = 0;

        if(isOpen())
            glfwGetWindowPos(window, &s.x , &s.y );

        return s;
    }

    void GLFW3WindowBackend::setPosition(int32_t x, int32_t y)
    {
        if(isOpen())
        {
            glfwSetWindowPos(window , x , y);
        }
    }

    Vec2I GLFW3WindowBackend::getSize() const
    {
        Vec2I s;
        s.x = 0;
        s.y = 0;

        if(isOpen())
            glfwGetWindowSize(window, &s.x, &s.y);

        return s;
    }

    void GLFW3WindowBackend::setSize(int32_t w, int32_t h)
    {
        glfwSetWindowSize(window, w, h);
    }

    void GLFW3WindowBackend::setTitle(const std::string& title)
    {
        glfwSetWindowTitle(window, title.c_str());
    }

    //void GLFW3WindowBackend::setIcon(const std::string &path_small , const std::string &path_big )
    void GLFW3WindowBackend::setIcon(uint32_t width, uint32_t height, const uint8_t* pixels)
    {
        //images[0] = load_icon(path_big.c_str());
        //images[1] = load_icon(path_small.c_str());

        //glfwSetWindowIcon(window, 2 ,images) 	
    }

    void GLFW3WindowBackend::setVisible(bool visible)
    {
        // still working on it
    }

    void GLFW3WindowBackend::setVSyncEnabled(bool enabled)
    {
        // still woriking on it
    }

    void GLFW3WindowBackend::setMouseCursorVisible(bool visible)
    {
        // still working on it
    }

    void GLFW3WindowBackend::setFramerateLimit(uint32_t limit)
    {
        //still woriking on it
    }

    bool GLFW3WindowBackend::setRenderingActive(bool active) const
    {
        // still working on it
    }

    void GLFW3WindowBackend::swapBuffers()
    {
        glfwSwapBuffers(window);
    }

    void GLFW3WindowBackend::lockCursor(bool lock)
    {
        if(isOpen())
        {
            // still working on it
        }
    }

    GLFW3WindowBackend::~GLFW3WindowBackend()
    {
        close();
    }
}
