#include <featherkit/structure/application.h>

namespace fea
{
    Application::Application() : shutDown(false)
    {
    }

    void Application::run()
    {
        while(!shutDown)
            loop();
    }

    void Application::quit()
    {
        shutDown = true;
    }
}
