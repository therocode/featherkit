namespace windstorm
{
    class Application
    {
        public:
            virtual void setup() = 0;
            virtual void run() = 0;
            virtual void destroy() = 0;
            void quit();
        protected:
            bool shutDown = false;
    };
}
