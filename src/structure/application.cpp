#include <fea/structure/application.hpp>
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

    Application::Application() : mShutDown(false)
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
        emscripten_set_main_loop(trampoline, 0, true);
#else
        while(!mShutDown)
            loop();
#endif
        destroy();
    }

    void Application::quit()
    {
        mShutDown = true;
    }
    
    bool Application::shuttingDown()
    {
        return mShutDown;
    }
}
