#pragma once

namespace fea
{
    class RenderMode
    {
        public:
            virtual void setup() = 0;
            virtual void preRender() = 0;
            virtual void postRender() = 0;
    };
}
