#pragma once
#include <featherkit/freetype-gl/texture-atlas.h>
#include <featherkit/freetype-gl/texture-font.h>
#include <featherkit/rendering/drawable2d.h>
#include <featherkit/rendering/text.h>
#include <featherkit/rendering/font.h>
#include <unordered_map>

namespace fea
{
    struct Writing
    {
        Writing(const std::wstring& t, const Font* f, const glm::vec2& p, const float s, const glm::vec3& c);
        const std::wstring text;
        const Font* font;
        const glm::vec2 penPosition;
        const float scale;
        const glm::vec3 colour;
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
            void setPenScale(const float s);
            void setPenColour(const glm::vec3& col);
            void setHorizontalAlign(const float coord);
            void newLine(const float distance, const float indentation = 0.0f);
            virtual RenderInfo getRenderInfo() const override;
            void rewrite();
            void clear();
        private:
            void addText(const std::wstring& text);
            void cacheFont(const Font& font);
            texture_atlas_t* atlas;
            const Font* currentFont;
            glm::vec2 pen;
            float scale;
            glm::vec3 colour;
            float horizontalAlign;
            uint32_t atlasSize;

            std::unordered_map<Font, texture_font_t*> fontCache;
            std::vector<Writing> writings;
    };
}
