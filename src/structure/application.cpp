#include <framework/structure/application.h>

namespace fk
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
