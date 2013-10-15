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
            if(!instance->shuttingDown())
                instance->loop();
            else
            {
                instance->destroy();
                instance = nullptr;
                emscripten_cancel_main_loop();
            }
        }
    }
#endif

    Application::Application() : shutDown(false)
    {
    }

    void Application::run(int argc, char** argv)
    {
        std::vector<std::string> args;

        for(int i = 0; i < argc; ++i)
        {
            args.push_back(std::string(argv[i]));
        }

        setup(args);
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
    
    bool Application::shuttingDown()
    {
        return shutDown;
    }
}
