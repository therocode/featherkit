#pragma once
#include <framework/rendering/drawable2d.h>

namespace windbreeze
{
    class Text : public Drawable2D
    {
        public:
            Text(std::string t) : text(t){isText = true;}
            std::string getText() const;
        protected:
            std::string text;
    };
}
