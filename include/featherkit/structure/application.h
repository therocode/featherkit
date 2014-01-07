#pragma once
#include <vector>
#include <string>

namespace fea
{
    class Application
    {
        public:
            Application();
            void run(int argc = 0, char** argv = nullptr);
            void quit();
            virtual void loop() = 0;
            bool shuttingDown();
            virtual void destroy() = 0;
        protected:
            virtual void setup(const std::vector<std::string>& args) = 0;
        private:
            bool shutDown;
    };
    /** @addtogroup Structure
     *@{
     *  @class Application
     *@}
     ***
     *  @class Application
     *  @brief Base class for the main application.
     *
     *  The purpose of this class is to have a standard way of creating and running an application. It manages everything in the application on the top most level. Would typically contain a GameStateMachine which in turn contains all states of the game. It is responsible for setting up and destroying things needed in general by the application.
     *
     *  Using this method, a typical main function running the application would look like this:
     *  @code
     *  int main()
     *  {
     *      ApplicationImplementation superGame;
     *
     *      superGame.run();
     *  }
     *  @endcode
     ***
     *  @fn void Application::run()
     *  @brief Run main loop of the application.
     *
     *  This function runs the main loop. When called, the main loop will be looping until Application::quit is called. The logic of the main loop is defined by inheriting from Application::loop.
     ***
     *  @fn void Application::quit()
     *  @brief Call this function to request the application to shut down.
     *
     *  After this function is called, it will leave the main loop after the current iteration is finished.
     ***
     *  @fn virtual void Application::setup(const std::vector<std::string>& args) = 0
     *  @brief Run setup procedures for the application.
     *
     *  This function is automatically called once before it starts looping the Application::loop() function when Application::run() is called. The string vector passed to the function contains the command line arguments passed to the executable.
     *  @param args Vector with command line arguments.
     ***
     *  @fn virtual void Application::loop() = 0
     *  @brief Iterate the main loop.
     *
     *  The application is given its logic by implementing this function. It is not meant to be called directly, instead it will automatically be called over and over, from Application::run.
     ***
     *  @fn bool Application::shuttingDown()
     *  @brief Check if the application is under the process of shutting down.
     *
     *  If the appication is shutting down, the current frame will be the last one.
     *  @return True if the application is shutting down.
     ***
     *  @fn virtual void Application::destroy() = 0
     *  @brief Run clean up procedures and shut down the application.
     *
     *  This function is not meant to be called directly. It is run bu the Application::run() function after the looping is over.
     ***/
}
