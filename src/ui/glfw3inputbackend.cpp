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
        
        glfwSetKeyCallback(window, KeyCallback);
        
        void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            switch(action)
            {
                case GLFW_PRESS:
                    switch(key)
                    {
                        case GLFW_KEY_A:
                        case GLFW_KEY_S:
                        case GLFW_KEY_D:
                        case GLFW_KEY_F:
                        case GLFW_KEY_G:
                        case GLFW_KEY_H:
                        case GLFW_KEY_J:
                        case GLFW_KEY_K:
                        case GLFW_KEY_L:
                        case GLFW_KEY_Z:
                        case GLFW_KEY_X:
                        case GLFW_KEY_C:
                        case GLFW_KEY_V:
                        case GLFW_KEY_B:
                        case GLFW_KEY_N:
                        case GLFW_KEY_M:
                        case GLFW_KEY_Q:
                        case GLFW_KEY_W:
                        case GLFW_KEY_E:
                        case GLFW_KEY_R:
                        case GLFW_KEY_T:
                        case GLFW_KEY_Y:
                        case GLFW_KEY_U:
                        case GLFW_KEY_I:
                        case GLFW_KEY_O:
                        case GLFW_KEY_P:
                        case GLFW_KEY_1:
                        case GLFW_KEY_2:
                        case GLFW_KEY_3:
                        case GLFW_KEY_4:
                        case GLFW_KEY_5:
                        case GLFW_KEY_6:
                        case GLFW_KEY_7:
                        case GLFW_KEY_8:
                        case GLFW_KEY_9:
                        case GLFW_KEY_0:
                        
                        
                    }
                
                case GLFW_RELEASE:
                    switch(key)
                    {
                        case GLFW_KEY_A:
                        case GLFW_KEY_S:
                        case GLFW_KEY_D:
                        case GLFW_KEY_F:
                        case GLFW_KEY_G:
                        case GLFW_KEY_H:
                        case GLFW_KEY_J:
                        case GLFW_KEY_K:
                        case GLFW_KEY_L:
                        case GLFW_KEY_Z:
                        case GLFW_KEY_X:
                        case GLFW_KEY_C:
                        case GLFW_KEY_V:
                        case GLFW_KEY_B:
                        case GLFW_KEY_N:
                        case GLFW_KEY_M:
                        case GLFW_KEY_Q:
                        case GLFW_KEY_W:
                        case GLFW_KEY_E:
                        case GLFW_KEY_R:
                        case GLFW_KEY_T:
                        case GLFW_KEY_Y:
                        case GLFW_KEY_U:
                        case GLFW_KEY_I:
                        case GLFW_KEY_O:
                        case GLFW_KEY_P:
                        case GLFW_KEY_1:
                        case GLFW_KEY_2:
                        case GLFW_KEY_3:
                        case GLFW_KEY_4:
                        case GLFW_KEY_5:
                        case GLFW_KEY_6:
                        case GLFW_KEY_7:
                        case GLFW_KEY_8:
                        case GLFW_KEY_9:
                        case GLFW_KEY_0:
                        
                    }
                
                case GLFW_REPEAT:
                    switch(key)
                    {
                        case GLFW_KEY_A:
                        case GLFW_KEY_S:
                        case GLFW_KEY_D:
                        case GLFW_KEY_F:
                        case GLFW_KEY_G:
                        case GLFW_KEY_H:
                        case GLFW_KEY_J:
                        case GLFW_KEY_K:
                        case GLFW_KEY_L:
                        case GLFW_KEY_Z:
                        case GLFW_KEY_X:
                        case GLFW_KEY_C:
                        case GLFW_KEY_V:
                        case GLFW_KEY_B:
                        case GLFW_KEY_N:
                        case GLFW_KEY_M:
                        case GLFW_KEY_Q:
                        case GLFW_KEY_W:
                        case GLFW_KEY_E:
                        case GLFW_KEY_R:
                        case GLFW_KEY_T:
                        case GLFW_KEY_Y:
                        case GLFW_KEY_U:
                        case GLFW_KEY_I:
                        case GLFW_KEY_O:
                        case GLFW_KEY_P:
                        case GLFW_KEY_1:
                        case GLFW_KEY_2:
                        case GLFW_KEY_3:
                        case GLFW_KEY_4:
                        case GLFW_KEY_5:
                        case GLFW_KEY_6:
                        case GLFW_KEY_7:
                        case GLFW_KEY_8:
                        case GLFW_KEY_9:
                        case GLFW_KEY_0:
                        
                    }
                
            }
            
        }
        return result;
    }


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
