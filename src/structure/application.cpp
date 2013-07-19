#include <framework/structure/application.h>

namespace windstorm
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
