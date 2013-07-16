#include <framework/structure/application.h>

namespace windstorm
{
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
