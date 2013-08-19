#include <featherkit/structure/application.h>

namespace fea
{
    Application::Application() : shutDown(false)
    {
    }

    void Application::run()
    {
        setup();
        while(!shutDown)
            loop();
        destroy();
    }

    void Application::quit()
    {
        shutDown = true;
    }
}
