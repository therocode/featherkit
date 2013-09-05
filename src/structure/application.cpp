#include <featherkit/structure/application.h>
#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

namespace fea
{
#ifdef EMSCRIPTEN
    static Application* instance = nullptr;

    void trampoline()
    {
        if(instance != nullptr)
        {
            instance->loop();
        }
        else
        {
        }
    }
#endif

    Application::Application() : shutDown(false)
    {
    }

    void Application::run()
    {
        setup();
#ifdef EMSCRIPTEN
        instance = this;
        emscripten_set_main_loop(trampoline, 60, true);
#else
        while(!shutDown)
            loop();
#endif
        destroy();
    }

    void Application::quit()
    {
        shutDown = true;
    }
}
