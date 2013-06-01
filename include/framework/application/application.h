namespace windstorm
{
    class Application
    {
        public:
            virtual void setup() = 0;
            void run();
            virtual void destroy() = 0;
            void quit();
        protected:
            virtual void loop() = 0;
        private:
            bool shutDown = false;
    };
    /** @addtogroup Application
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
     *      superGame.setup();
     *      superGame.run();
     *      superGame.destroy();
     *  }
     *  @endcode
     ***
     *  @fn virtual void setup() = 0
     *  @brief Run setup procedures for the application.
     ***
     *  @fn virtual void run() = 0
     *  @brief Run main loop of the application.
     *
     *  This function contains the main loop. When it is started using this function, it will keep on running 
     **/
}
