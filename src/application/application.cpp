#include "framework/application/application.h"

namespace windstorm
{
    void Application::quit()
    {
        shutDown = true;
    }
}
