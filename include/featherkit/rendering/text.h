#pragma once
#include <string>

namespace fea
{
    class Font;

    struct Text
    {
        Text(std::string t);
        std::string text;
        Font* font;
    };
}
