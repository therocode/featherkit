#include <fea/ui/glfw3inputbackend.hpp>

namespace fea
{
    GLFW3InputBackend::GLFW3InputBackend():
        mKeyRepeat(true)
    {
    }

    std::queue<Event> GLFW3InputBackend::fetchEvents()
    {
        
        std::queue<Event> result;
        void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
-           
-                
+           switch(action){
+           case GLFW_PRESS:
+                switch(key)
+                         {
+                        case GLFW_KEY_E:
+                            KeyEvent event;
+                            Code code(4);
+                            event = key_press(code,false,false,false,false);
                             result.push(event);
+                            break;
+                         }
+                break;
+                }
+           
+       
            
        }
     
         
     
    return result;}


    bool GLFW3InputBackend::isKeyPressed(Keyboard::Code code)
    {
        return false;
    }

    bool GLFW3InputBackend::isMouseButtonPressed(Mouse::Button b)
    {
        return false;
    }

    Vec2I GLFW3InputBackend::getMouseGlobalPosition()
    {
        return {};
    }

    Vec2I GLFW3InputBackend::getMouseWindowPosition()
    {
        return {};
    }

    void GLFW3InputBackend::setMouseGlobalPosition(int32_t x, int32_t y)
    {
    }

    void GLFW3InputBackend::setMouseWindowPosition(int32_t x, int32_t y)
    {
    }

    bool GLFW3InputBackend::isGamepadConnected(uint32_t id)
    {
        return true;
    }

    uint32_t GLFW3InputBackend::getGamepadButtonCount(uint32_t id)
    {
        return 0;
    }

    bool GLFW3InputBackend::isGamepadButtonPressed(uint32_t id, uint32_t button)
    {
        return false;
    }

    bool GLFW3InputBackend::gamepadHasAxis(uint32_t id, Gamepad::Axis axis)
    {
        return false;
    }

    float GLFW3InputBackend::getGamepadAxisPosition(uint32_t id, Gamepad::Axis axis)
    {
        return 0.0f;
    }

    void GLFW3InputBackend::setGamepadThreshold(float threshold)
    {
        (void) threshold;
    }

    void GLFW3InputBackend::setKeyRepeatEnabled(bool enabled)
    {
        (void) enabled;
    }
}
