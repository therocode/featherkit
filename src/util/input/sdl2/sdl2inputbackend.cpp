#include <featherkit/util/input/sdl2/sdl2inputbackend.h>

namespace fea
{
    namespace util
    {
        SDL2InputBackend::SDL2InputBackend()
        {
            //SDL_EnableKeyRepeat(500, 30);
        }

        std::queue<Event> SDL2InputBackend::fetchEvents()
        {
            SDL_Event event;
            std::queue<Event> result;
            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
				{
                    result.push(closed());
				}
				else if(event.type == SDL_WINDOWEVENT)
				{
					if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                    	result.push(resized(event));
					else if(event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
						result.push(windowFocus(false));
					else if(event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
						result.push(windowFocus(true));
				}
                else if(event.type == SDL_KEYDOWN)
                    result.push(keyPressed(event));
                else if(event.type == SDL_KEYUP)
                    result.push(keyReleased(event));
                else if(event.type == SDL_MOUSEBUTTONDOWN)
                    result.push(mouseButtonPressed(event));
                else if(event.type == SDL_MOUSEBUTTONUP)
                    result.push(mouseButtonReleased(event));
                else if(event.type == SDL_MOUSEMOTION)
                    result.push(mouseMoved(event));
                else if(event.type == SDL_JOYBUTTONDOWN)
                    result.push(gamepadButtonPressed(event));
                else if(event.type == SDL_JOYBUTTONUP)
                    result.push(gamepadButtonReleased(event));
                else if(event.type == SDL_JOYAXISMOTION)
                    result.push(gamepadMoved(event));
            }

            return result;
        }

        bool SDL2InputBackend::isKeyPressed(Keyboard::Code code)
        {
            const uint8_t* keymap = (uint8_t*)SDL_GetKeyboardState(NULL);
            return keymap[feaKeyCodeToSdl(code)];
        }

        bool SDL2InputBackend::isMouseButtonPressed(Mouse::Button b)
        {
            return SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(feaMouseButtonToSdl(b));
        }

        glm::ivec2 SDL2InputBackend::getMouseGlobalPosition()
        {
            //will be local only, not global
            int x, y;
            SDL_GetMouseState(&x, &y);
            return glm::ivec2(x, y);
        }

        glm::ivec2 SDL2InputBackend::getMouseWindowPosition()
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            return glm::ivec2(x, y);
        }

        void SDL2InputBackend::setMouseGlobalPosition(int32_t x, int32_t y)
        {
            //works locally, not globlaly
            //SDL_WarpMouse((uint16_t)x, (uint16_t)y);
        }

        void SDL2InputBackend::setMouseWindowPosition(int32_t x, int32_t y)
        {
            //SDL_WarpMouse((uint16_t)x, (uint16_t)y);
        }

        bool SDL2InputBackend::isGamepadConnected(uint32_t id)
        {
            (void)id;
            //not sure
            return true;
        }

        uint32_t SDL2InputBackend::getGamepadButtonCount(uint32_t id)
        {
            (void)id;
            //not sure
            return 0;
        }

        bool SDL2InputBackend::isGamepadButtonPressed(uint32_t id, uint32_t button)
        {
            (void)id;
            (void)button;
            //not sure
            return false;
        }

        bool SDL2InputBackend::gamepadHasAxis(uint32_t id, Gamepad::Axis axis)
        {
            (void)id;
            (void)axis;
            //not sure
            return false;
        }

        float SDL2InputBackend::getGamepadAxisPosition(uint32_t id, Gamepad::Axis axis)
        {
            (void)id;
            (void)axis;
            //not sure
            return 0.0f;
        }

        Event SDL2InputBackend::closed()
        {
            Event result;

            result.type = Event::CLOSED;

            return result;
        }

        Event SDL2InputBackend::resized(SDL_Event& event)
        {
            Event result;

            result.type = Event::RESIZED;
            result.size.width = (uint32_t)event.window.data1;
            result.size.height = (uint32_t)event.window.data2;

            return result;
        }

		Event SDL2InputBackend::windowFocus(bool focus)
		{
			Event result;
			if(focus)
				result.type = Event::GAINEDFOCUS;
			else
				result.type = Event::LOSTFOCUS;

			return result;
		}
        Event SDL2InputBackend::active(SDL_Event& event)
        {
            //TBI
            (void) event;
            Event result;

            result.type = Event::LOSTFOCUS;

            return result;
        }

        Event SDL2InputBackend::keyPressed(SDL_Event& event)
        {
            Event result;

            result.type = Event::KEYPRESSED;
            result.key.code = sdlKeyCodeToFea(event.key.keysym.sym);

            //these not fixed
            //result.key.alt = event.key.alt;
            //result.key.control = event.key.control;
            //result.key.shift = event.key.shift;
            //result.key.system = event.key.system;

            return result;
        }

        Event SDL2InputBackend::keyReleased(SDL_Event& event)
        {
            Event result;

            result.type = Event::KEYRELEASED;
            result.key.code = sdlKeyCodeToFea(event.key.keysym.sym);

            //these not fixed
            //result.key.alt = event.key.alt;
            //result.key.control = event.key.control;
            //result.key.shift = event.key.shift;
            //result.key.system = event.key.system;

            return result;
        }

        Event SDL2InputBackend::mouseButtonPressed(SDL_Event& event)
        {
            Event result;
            result.mouseButton.x = event.button.x;
            result.mouseButton.y = event.button.y;

            uint32_t button = event.button.button;

            if(button == 1 || button == 2 || button == 3)
            {
                result.type = Event::MOUSEBUTTONPRESSED;
                result.mouseButton.button = sdlMouseButtonToFea(button);
            }
            else if(button == 4 || button == 5)
            {
                result.type = Event::MOUSEWHEELMOVED;

                if(button == 4)
                    result.mouseWheel.delta = -1;
                else
                    result.mouseWheel.delta = 1;
            }

            return result;
        }

        Event SDL2InputBackend::mouseButtonReleased(SDL_Event& event)
        {
            Event result;

            result.type = Event::MOUSEBUTTONRELEASED;
            result.mouseButton.button = sdlMouseButtonToFea(event.button.button);
            result.mouseButton.x = event.button.x;
            result.mouseButton.y = event.button.y;

            return result;
        }

        Event SDL2InputBackend::mouseMoved(SDL_Event& event)
        {
            Event result;

            result.type = Event::MOUSEMOVED;
            result.mouseMove.x = event.motion.x;
            result.mouseMove.y = event.motion.y;
			result.mouseMove.relx = event.motion.xrel;
			result.mouseMove.rely = event.motion.yrel;

            return result;
        }

        Event SDL2InputBackend::gamepadButtonPressed(SDL_Event& event)
        {
            //TBI
            Event result;
            result.type = Event::GAMEPADBUTTONPRESSED;
            (void)event;
            //result.gamepadButton.gamepadId = event.joystickButton.joystickId;
            //result.gamepadButton.button = event.joystickButton.button;
            return result;
        }

        Event SDL2InputBackend::gamepadButtonReleased(SDL_Event& event)
        {
            //TBI
            Event result;
            result.type = Event::GAMEPADBUTTONRELEASED;
            (void)event;
            //result.gamepadButton.gamepadId = event.joystickButton.joystickId;
            //result.gamepadButton.button = event.joystickButton.button;
            return result;
        }

        Event SDL2InputBackend::gamepadMoved(SDL_Event& event)
        {
            //TBI
            Event result;
            result.type = Event::GAMEPADMOVED;
            (void)event;
            //result.gamepadMove.axis = (Gamepad::Axis) event.joystickMove.axis; 
            //result.gamepadMove.gamepadId = (Gamepad::Axis) event.joystickMove.joystickId;
            //result.gamepadMove.position = event.joystickMove.position;
            return result;
        }

        void SDL2InputBackend::setGamepadThreshold(float threshold)
        {
            //TBI
            //window.setJoystickThreshold(threshold);
            (void) threshold;
        }

        void SDL2InputBackend::setKeyRepeatEnabled(bool enabled)
        {
            //TBI
            //window.setKeyRepeatEnabled(enabled);
            (void) enabled;
        }


        Keyboard::Code SDL2InputBackend::sdlKeyCodeToFea(SDL_Keycode sdlCode) const
        {
            switch(sdlCode)
            {
                case SDLK_a:
                    return Keyboard::A;
                case SDLK_b:
                    return Keyboard::B;
                case SDLK_c:
                    return Keyboard::C;
                case SDLK_d:
                    return Keyboard::D;
                case SDLK_e:
                    return Keyboard::E;
                case SDLK_f:
                    return Keyboard::F;
                case SDLK_g:
                    return Keyboard::G;
                case SDLK_h:
                    return Keyboard::H;
                case SDLK_i:
                    return Keyboard::I;
                case SDLK_j:
                    return Keyboard::J;
                case SDLK_k:
                    return Keyboard::K;
                case SDLK_l:
                    return Keyboard::L;
                case SDLK_m:
                    return Keyboard::M;
                case SDLK_n:
                    return Keyboard::N;
                case SDLK_o:
                    return Keyboard::O;
                case SDLK_p:
                    return Keyboard::P;
                case SDLK_q:
                    return Keyboard::Q;
                case SDLK_r:
                    return Keyboard::R;
                case SDLK_s:
                    return Keyboard::S;
                case SDLK_t:
                    return Keyboard::T;
                case SDLK_u:
                    return Keyboard::U;
                case SDLK_v:
                    return Keyboard::V;
                case SDLK_w:
                    return Keyboard::W;
                case SDLK_x:
                    return Keyboard::X;
                case SDLK_y:
                    return Keyboard::Y;
                case SDLK_z:
                    return Keyboard::Z;
                case SDLK_0:
                    return Keyboard::NUM0;
                case SDLK_1:
                    return Keyboard::NUM1;
                case SDLK_2:
                    return Keyboard::NUM2;
                case SDLK_3:
                    return Keyboard::NUM3;
                case SDLK_4:
                    return Keyboard::NUM4;
                case SDLK_5:
                    return Keyboard::NUM5;
                case SDLK_6:
                    return Keyboard::NUM6;
                case SDLK_7:
                    return Keyboard::NUM7;
                case SDLK_8:
                    return Keyboard::NUM8;
                case SDLK_9:
                    return Keyboard::NUM9;
                case SDLK_ESCAPE:
                    return Keyboard::ESCAPE;
                case SDLK_LCTRL:
                    return Keyboard::LCONTROL;
                case SDLK_LSHIFT:
                    return Keyboard::LSHIFT;
                case SDLK_LALT:
                    return Keyboard::LALT;
                case SDLK_LGUI:
                    return Keyboard::LSYSTEM;
                case SDLK_RCTRL:
                    return Keyboard::RCONTROL;
                case SDLK_RSHIFT:
                    return Keyboard::RSHIFT;
                case SDLK_RALT:
                    return Keyboard::RALT;
                case SDLK_RGUI:
                    return Keyboard::RSYSTEM;
                case SDLK_MENU:
                    return Keyboard::MENU;
                case SDLK_LEFTBRACKET:
                    return Keyboard::LBRACKET;
                case SDLK_RIGHTBRACKET:
                    return Keyboard::RBRACKET;
                case SDLK_SEMICOLON:
                    return Keyboard::SEMICOLON;
                case SDLK_COMMA:
                    return Keyboard::COMMA;
                case SDLK_PERIOD:
                    return Keyboard::PERIOD;
                case SDLK_QUOTE:
                    return Keyboard::QUOTE;
                case SDLK_SLASH:
                    return Keyboard::SLASH;
                case SDLK_BACKSLASH:
                    return Keyboard::BACKSLASH;
                case SDLK_BACKQUOTE:
                    return Keyboard::TILDE;
                case SDLK_EQUALS:
                    return Keyboard::EQUAL;
                case SDLK_MINUS:
                    return Keyboard::DASH;
                case SDLK_SPACE:
                    return Keyboard::SPACE;
                case SDLK_RETURN:
                    return Keyboard::RETURN;
                case SDLK_BACKSPACE:
                    return Keyboard::BACKSPACE;
                case SDLK_TAB:
                    return Keyboard::TAB;
                case SDLK_PAGEUP:
                    return Keyboard::PAGEUP;
                case SDLK_PAGEDOWN:
                    return Keyboard::PAGEDOWN;
                case SDLK_END:
                    return Keyboard::END;
                case SDLK_HOME:
                    return Keyboard::HOME;
                case SDLK_INSERT:
                    return Keyboard::INSERT;
                case SDLK_DELETE:
                    return Keyboard::DELETE;
                case SDLK_KP_PLUS:
                    return Keyboard::ADD;
                case SDLK_KP_MINUS:
                    return Keyboard::SUBTRACT;
                case SDLK_KP_MULTIPLY:
                    return Keyboard::MULTIPLY;
                case SDLK_KP_DIVIDE:
                    return Keyboard::DIVIDE;
                case SDLK_LEFT:
                    return Keyboard::LEFT;
                case SDLK_RIGHT:
                    return Keyboard::RIGHT;
                case SDLK_UP:
                    return Keyboard::UP;
                case SDLK_DOWN:
                    return Keyboard::DOWN;
                case SDLK_KP_0:
                    return Keyboard::NUMPAD0;
                case SDLK_KP_1:
                    return Keyboard::NUMPAD1;
                case SDLK_KP_2:
                    return Keyboard::NUMPAD2;
                case SDLK_KP_3:
                    return Keyboard::NUMPAD3;
                case SDLK_KP_4:
                    return Keyboard::NUMPAD4;
                case SDLK_KP_5:
                    return Keyboard::NUMPAD5;
                case SDLK_KP_6:
                    return Keyboard::NUMPAD6;
                case SDLK_KP_7:
                    return Keyboard::NUMPAD7;
                case SDLK_KP_8:
                    return Keyboard::NUMPAD8;
                case SDLK_KP_9:
                    return Keyboard::NUMPAD9;
                case SDLK_F1:
                    return Keyboard::F1;
                case SDLK_F2:
                    return Keyboard::F2;
                case SDLK_F3:
                    return Keyboard::F3;
                case SDLK_F4:
                    return Keyboard::F4;
                case SDLK_F5:
                    return Keyboard::F5;
                case SDLK_F6:
                    return Keyboard::F6;
                case SDLK_F7:
                    return Keyboard::F7;
                case SDLK_F8:
                    return Keyboard::F8;
                case SDLK_F9:
                    return Keyboard::F9;
                case SDLK_F10:
                    return Keyboard::F10;
                case SDLK_F11:
                    return Keyboard::F11;
                case SDLK_F12:
                    return Keyboard::F12;
                case SDLK_F13:
                    return Keyboard::F13;
                case SDLK_F14:
                    return Keyboard::F14;
                case SDLK_F15:
                    return Keyboard::F15;
                case SDLK_PAUSE:
                    return Keyboard::PAUSE;
                default:
                    return Keyboard::UNKNOWN;
            }
        }

        SDL_Keycode SDL2InputBackend::feaKeyCodeToSdl(Keyboard::Code feaCode) const
        {
            switch(feaCode)
            {
                case Keyboard::UNKNOWN:
                    return (SDL_Keycode)-1;
                case Keyboard::A:
                    return SDLK_a;
                case Keyboard::B:
                    return SDLK_b;
                case Keyboard::C:
                    return SDLK_c;
                case Keyboard::D:
                    return SDLK_d;
                case Keyboard::E:
                    return SDLK_e;
                case Keyboard::F:
                    return SDLK_f;
                case Keyboard::G:
                    return SDLK_g;
                case Keyboard::H:
                    return SDLK_h;
                case Keyboard::I:
                    return SDLK_i;
                case Keyboard::J:
                    return SDLK_j;
                case Keyboard::K:
                    return SDLK_k;
                case Keyboard::L:
                    return SDLK_l;
                case Keyboard::M:
                    return SDLK_m;
                case Keyboard::N:
                    return SDLK_n;
                case Keyboard::O:
                    return SDLK_o;
                case Keyboard::P:
                    return SDLK_p;
                case Keyboard::Q:
                    return SDLK_q;
                case Keyboard::R:
                    return SDLK_r;
                case Keyboard::S:
                    return SDLK_s;
                case Keyboard::T:
                    return SDLK_t;
                case Keyboard::U:
                    return SDLK_u;
                case Keyboard::V:
                    return SDLK_v;
                case Keyboard::W:
                    return SDLK_w;
                case Keyboard::X:
                    return SDLK_x;
                case Keyboard::Y:
                    return SDLK_y;
                case Keyboard::Z:
                    return SDLK_z;
                case Keyboard::NUM0:
                    return SDLK_0;
                case Keyboard::NUM1:
                    return SDLK_1;
                case Keyboard::NUM2:
                    return SDLK_2;
                case Keyboard::NUM3:
                    return SDLK_3;
                case Keyboard::NUM4:
                    return SDLK_4;
                case Keyboard::NUM5:
                    return SDLK_5;
                case Keyboard::NUM6:
                    return SDLK_6;
                case Keyboard::NUM7:
                    return SDLK_7;
                case Keyboard::NUM8:
                    return SDLK_8;
                case Keyboard::NUM9:
                    return SDLK_9;
                case Keyboard::ESCAPE:
                    return SDLK_ESCAPE;
                case Keyboard::LCONTROL:
                    return SDLK_LCTRL;
                case Keyboard::LSHIFT:
                    return SDLK_LSHIFT;
                case Keyboard::LALT:
                    return SDLK_LALT;
                case Keyboard::LSYSTEM:
                    return SDLK_LGUI;
                case Keyboard::RCONTROL:
                    return SDLK_RCTRL;
                case Keyboard::RSHIFT:
                    return SDLK_RSHIFT;
                case Keyboard::RALT:
                    return SDLK_RALT;
                case Keyboard::RSYSTEM:
                    return SDLK_RGUI;
                case Keyboard::MENU:
                    return SDLK_MENU;
                case Keyboard::LBRACKET:
                    return SDLK_LEFTBRACKET;
                case Keyboard::RBRACKET:
                    return SDLK_RIGHTBRACKET;
                case Keyboard::SEMICOLON:
                    return SDLK_SEMICOLON;
                case Keyboard::COMMA:
                    return SDLK_COMMA;
                case Keyboard::PERIOD:
                    return SDLK_PERIOD;
                case Keyboard::QUOTE:
                    return SDLK_QUOTE;
                case Keyboard::SLASH:
                    return SDLK_SLASH;
                case Keyboard::BACKSLASH:
                    return SDLK_BACKSLASH;
                case Keyboard::TILDE:
                    return SDLK_BACKQUOTE;
                case Keyboard::EQUAL:
                    return SDLK_EQUALS;
                case Keyboard::DASH:
                    return SDLK_MINUS;
                case Keyboard::SPACE:
                    return SDLK_SPACE;
                case Keyboard::RETURN:
                    return SDLK_RETURN;
                case Keyboard::BACKSPACE:
                    return SDLK_BACKSPACE;
                case Keyboard::TAB:
                    return SDLK_TAB;
                case Keyboard::PAGEUP:
                    return SDLK_PAGEUP;
                case Keyboard::PAGEDOWN:
                    return SDLK_PAGEDOWN;
                case Keyboard::END:
                    return SDLK_END;
                case Keyboard::HOME:
                    return SDLK_HOME;
                case Keyboard::INSERT:
                    return SDLK_INSERT;
                case Keyboard::DELETE:
                    return SDLK_DELETE;
                case Keyboard::ADD:
                    return SDLK_KP_PLUS;
                case Keyboard::SUBTRACT:
                    return SDLK_KP_MINUS;
                case Keyboard::MULTIPLY:
                    return SDLK_KP_MULTIPLY;
                case Keyboard::DIVIDE:
                    return SDLK_KP_DIVIDE;
                case Keyboard::LEFT:
                    return SDLK_LEFT;
                case Keyboard::RIGHT:
                    return SDLK_RIGHT;
                case Keyboard::UP:
                    return SDLK_UP;
                case Keyboard::DOWN:
                    return SDLK_DOWN;
                case Keyboard::NUMPAD0:
                    return SDLK_KP_0;
                case Keyboard::NUMPAD1:
                    return SDLK_KP_1;
                case Keyboard::NUMPAD2:
                    return SDLK_KP_2;
                case Keyboard::NUMPAD3:
                    return SDLK_KP_3;
                case Keyboard::NUMPAD4:
                    return SDLK_KP_4;
                case Keyboard::NUMPAD5:
                    return SDLK_KP_5;
                case Keyboard::NUMPAD6:
                    return SDLK_KP_6;
                case Keyboard::NUMPAD7:
                    return SDLK_KP_7;
                case Keyboard::NUMPAD8:
                    return SDLK_KP_8;
                case Keyboard::NUMPAD9:
                    return SDLK_KP_9;
                case Keyboard::F1:
                    return SDLK_F1;
                case Keyboard::F2:
                    return SDLK_F2;
                case Keyboard::F3:
                    return SDLK_F3;
                case Keyboard::F4:
                    return SDLK_F4;
                case Keyboard::F5:
                    return SDLK_F5;
                case Keyboard::F6:
                    return SDLK_F6;
                case Keyboard::F7:
                    return SDLK_F7;
                case Keyboard::F8:
                    return SDLK_F8;
                case Keyboard::F9:
                    return SDLK_F9;
                case Keyboard::F10:
                    return SDLK_F10;
                case Keyboard::F11:
                    return SDLK_F11;
                case Keyboard::F12:
                    return SDLK_F12;
                case Keyboard::F13:
                    return SDLK_F13;
                case Keyboard::F14:
                    return SDLK_F14;
                case Keyboard::F15:
                    return SDLK_F15;
                case Keyboard::PAUSE:
                    return SDLK_PAUSE;
            }
        }
        
        uint8_t SDL2InputBackend::feaMouseButtonToSdl(Mouse::Button feaMouseButton) const
        {
            switch(feaMouseButton)
            {
                case Mouse::LEFT:
                    return 1;
                case Mouse::RIGHT:
                    return 3;
                case Mouse::MIDDLE:
                    return 2;
                case Mouse::XBUTTON1:
                    return 1;
                case Mouse::XBUTTON2:
                    return 3;
            }
        }
        
        Mouse::Button SDL2InputBackend::sdlMouseButtonToFea(uint32_t sdlMouseButton) const
        {
            switch(sdlMouseButton)
            {
                case 1:
                    return Mouse::LEFT;
                case 3:
                    return Mouse::RIGHT;
                case 2:
                    return Mouse::MIDDLE;
                default:
                    return Mouse::LEFT;
            }
        }
    }
}
