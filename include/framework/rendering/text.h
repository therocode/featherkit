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
            void setText();
            glm::vec3 getColour() const;
            void setColour(glm::vec3 c);
            float getFontSize() const;
            void setFontSize(float size);
            int32_t getFont() const;
            void setFont(int32_t f);
        protected:
            std::string text;
            glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f);
            float fontSize = 24.0f;
            int font;
    };
}
