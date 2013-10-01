#pragma once
#include <freetype-gl.h>
#include <featherkit/rendering/drawable2d.h>
#include <featherkit/rendering/text.h>
#include <featherkit/rendering/font.h>
#include <unordered_map>

namespace fea
{
    struct Writing
    {
        Writing(const std::wstring& t, const Font* f, const glm::vec2& p);
        const std::wstring text;
        const Font* font;
        const glm::vec2 penPosition;
    };

    class TextSurface : public Drawable2D
    {
        public:
            TextSurface();
            ~TextSurface();
            void write(const std::string& text);
            void write(const std::wstring& text);
            void setPenFont(const Font& font);
            void setPenPosition(const glm::vec2 pos);
            void setHorizontalAlign(const float coord);
            void newLine(const float distance, const float indentation = 0.0f);
            virtual RenderInfo getRenderInfo() const override;
            void rewrite();
            void clear();
        private:
            void addText(const std::wstring& text);
            texture_atlas_t* atlas;
            const Font* currentFont;
            glm::vec2 pen;
            float horizontalAlign;

            std::unordered_map<Font, texture_font_t*> fontCache;
            std::vector<Writing> writings;
    };
}
