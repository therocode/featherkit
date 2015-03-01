#pragma once
#include <fea/config.hpp>
#include <fea/freetype-gl/texture-atlas.h>
#include <fea/freetype-gl/texture-font.h>
#include <fea/rendering/drawable2d.hpp>
#include <fea/rendering/font.hpp>
#include <unordered_map>

namespace fea
{

    class FEA_API TextSurface : public Drawable2D
    {
        struct Writing
        {
            Writing(const std::wstring& text, const Font* font, const glm::vec2& penPosition, float scale, const Color& color, bool positionSet);
            std::wstring mText;
            const Font* mFont;
            glm::vec2 mPenPosition;
            float mScale;
            Color mColor;
            bool mPositionSet;
        };

    public:
        TextSurface();
        ~TextSurface();
        TextSurface(const TextSurface& other) = delete;
        TextSurface(TextSurface&& other);
        TextSurface& operator=(const TextSurface& other) = delete;
        TextSurface& operator=(TextSurface&& other);
        void write(const std::string& text);
        void write(const std::wstring& text);
        void setPenFont(const Font& font);
        void setPenPosition(const glm::vec2 position);
        void setPenScale(float scale);
        void setPenColor(const Color& color);
        void setHorizontalAlign(float coord);
        void setLineHeight(float height);
        void setLineWidth(float width);
        void enableWordWrap(bool enabled);
        void newLine(float distance, float indentation = 0.0f);
        void newLine();
        virtual std::vector<RenderEntity> getRenderInfo() const override;
        void clear();
        glm::vec2 getSize();
    private:
        void rewrite();
        void addText(const std::wstring& text);
        void cacheFont(const Font& font);
        texture_atlas_t* mAtlas;
        const Font* mCurrentFont;
        glm::vec2 mPenPosition;
        glm::vec2 mPenSetPosition;
        bool mPenSet;
        float mScale;
        Color mColor;
        float mHorizontalAlign;
        float mLineHeight;
        float mLineWidth;
        bool mWordWrap;
        uint32_t mAtlasSize;

        std::unordered_map<Font, texture_font_t*> mFontCache;
        std::vector<Writing> mWritings;

        glm::vec2 mLowBounds;
        glm::vec2 mHighBounds;
    };
    /** @addtogroup Rendering
     *@{
     *  @class TextSurface
     *@}
     ***
     *  @class TextSurface
     *  @brief A drawable for text.
     *
     *  This drawable is similar to a piece of paper. Text can be written on it using the TextSurface::write method. All added text is appended to the current pen position and the pen position is advanced accordingly. The pen itself has states defining its color, current font, and scale. When these attributes are set, all text written with the pen will be affected.
     *
     ***
     *  @fn TextSurface::TextSurface()
     *  @brief Construct a TextSurface.
     ***
     *  @fn TextSurface::TextSurface(TextSurface&& other)
     *  @brief Move constructor.
     *  @param other Other instance.
     ***
     *  @fn TextSurface::TextSurface(const TextSurface& other) = delete
     *  @brief Deleted copy constructor.
     *  @param other Instance to copy.
     ***
     *  @fn TextSurface& TextSurface::operator=(TextSurface&& other)
     *  @brief Move assignment operator.
     *  @param other Other instance.
     ***
     *  @fn TextSurface& TextSurface::operator=(const TextSurface& other)
     *  @brief Deleted assignment operator.
     *  @param other Other instance.
     ***
     *  @fn void TextSurface::write(const std::string& text)
     *  @brief Write text at the current pen position.
     *
     *  The position of the pen is moved forward accordingly. The pen's current state determines the scale, font and color of the text.
     *  @param text Text to write.
     ***
     *  @fn void TextSurface::write(const std::wstring& text)
     *  @brief Write text at the current pen position.
     *
     *  The position of the pen is moved forward accordingly. The pen's current state determines the scale, font and color of the text.
     *  @param text Text to write.
     ***
     *  @fn void TextSurface::setPenFont(const Font& font)
     *  @brief Change the current font of the pen.
     *
     *  If the text is too grainy or has a lot of artifacts, try increasing the size of the font.
     *  @param font Font to use.
     ***
     *  @fn void TextSurface::setPenPosition(const glm::vec2 position)
     *  @brief Set the current pen position.
     *  @param position New position.
     ***
     *  @fn void TextSurface::setPenScale(float scale)
     *  @brief Set the current pen scale.
     *
     *  Scaling can make text appear grainy. If a higher resolution of the text is needed, increase the size of the font.
     *  @param scale New scale.
     ***
     *  @fn void TextSurface::setPenColor(const Color& color)
     *  @brief Set the current pen color.
     *  @param color New color.
     ***
     *  @fn void TextSurface::setHorizontalAlign(float coord)
     *  @brief Set the horizontal alignment for new text lines.
     *
     *  When a new line is issued using the TextSurface::newLine method or when it word wraps, the pen is moved down under the current line, aligned to this value on the X axis.
     *  @param coord X coordinate to align to.
     ***
     *  @fn void TextSurface::setLineHeight(float height)
     *  @brief Set the spacing between each line.
     *
     *  The spacing is maintained when the pen moves to a new line.
     *
     *  Default is 0.
     *  @param height Height.
     ***
     *  @fn void TextSurface::setLineWidth(float width)
     *  @brief Set how long lines should be.
     *
     *  If word wrapping is enabled, new lines will be issued automatically when required to not exceed the line width. Words will be conserved as possible.
     *
     *  Default is 0.
     *  @param width Maximum line width.
     ***
     *  @fn void TextSurface::enableWordWrap(bool enabled)
     *  @brief Enable word wrapping.
     *
     *  Word wrapping causes the pen to automatically move to a new line to prevent the line from exceeding the current line width set by setLineWidth. If a word would exceed the limit, the whole word is moved to the next line. If a word is longer than the line width, the word will be split up.
     *
     *  Default is disabled.
     *  @param enabled True if enabled.
     ***
     *  @fn void TextSurface::newLine(float distance, float indentation = 0.0f)
     *  @brief Move the pen to a new line.
     *
     *  The pen is moved downwards with the amount given by the distance parameter. The X position of the pen will be set to the horizontal alignment given by TextSurface::setHorizontalAlign.
     *  @param distance Distance to move downwards. Can be negative.
     *  @param indentation Optional indentation to deviate from the horizontal alignment.
     ***
     *  @fn void TextSurface::newLine()
     *  @brief Move the pen to a new line.
     *
     *  This overload of newLine uses the values set by setLineWidth and has no indentation.
     ***
     *  @fn void TextSurface::clear()
     *  @brief Clear all text written on the text area.
     ***
     *  @fn glm::vec2 TextSurface::getSize()
     *  @brief Get the size of the bounding rectangle for all text on the surface
     *  @return Size.
     ***/
}
