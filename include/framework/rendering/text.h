#pragma once
#include <framework/rendering/drawable2d.h>

namespace windbreeze
{
    class Text : public Drawable2D
    {
        public:
            Text(std::string t) : text(t){isText = true;}
            Text(std::string t, glm::vec3 c) : text(t), colour(c){isText = true;}
            std::string getText() const;
            glm::vec3 getColour() const;
            void setColour(glm::vec3 c);
        protected:
            std::string text;
            glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f);
    };
}
