#include <fea/rendering/color.hpp>

namespace fea
{
    Color::Color()
    {
        mRed = 0u;
        mGreen = 0u;
        mBlue = 0u;
        mAlpha = 255u;
    }

    Color::Color(float r, float g, float b, float a)
    {
        mRed   = (uint8_t)(std::max(0.0f, std::min(1.0f, r)) * 255.0f);
        mGreen = (uint8_t)(std::max(0.0f, std::min(1.0f, g)) * 255.0f);
        mBlue  = (uint8_t)(std::max(0.0f, std::min(1.0f, b)) * 255.0f);
        mAlpha = (uint8_t)(std::max(0.0f, std::min(1.0f, a)) * 255.0f);
    }

    Color::Color(int32_t r, int32_t g, int32_t b, int32_t a)
    {
        mRed   = std::max(0, std::min(255, r));
        mGreen = std::max(0, std::min(255, g));
        mBlue  = std::max(0, std::min(255, b));
        mAlpha = std::max(0, std::min(255, a));
    }

    Color::Color(int32_t hexValue, float a)
    {
        hexValue = std::max(0, std::min(0xFFFFFF, hexValue));

        mRed   = (hexValue >> 16) & 0xFF;
        mGreen = (hexValue >>  8) & 0xFF;
        mBlue  =  hexValue & 0xFF;
        mAlpha = (uint8_t)(std::max(0.0f, std::min(1.0f, a)) * 255.0f);
    }

    Color::Color(int32_t hexValue, int32_t a)
    {
        hexValue = std::max(0, std::min(0xFFFFFF, hexValue));

        mRed   = (hexValue >> 16) & 0xFF;
        mGreen = (hexValue >>  8) & 0xFF;
        mBlue  =  hexValue & 0xFF;
        mAlpha = std::max(0, std::min(255, a));
    }

    Color Color::operator+(const Color& other) const
    {
        Color result;

        result.mRed   = (uint8_t)std::min((int16_t)mRed   + other.mRed,   255);
        result.mGreen = (uint8_t)std::min((int16_t)mGreen + other.mGreen, 255);
        result.mBlue  = (uint8_t)std::min((int16_t)mBlue  + other.mBlue,  255);
        result.mAlpha = (uint8_t)std::min((int16_t)mAlpha + other.mAlpha, 255);

        return result;
    }

    Color& Color::operator+=(const Color& other)
    {
        mRed   = (uint8_t)std::min((int16_t)mRed   + other.mRed,   255);
        mGreen = (uint8_t)std::min((int16_t)mGreen + other.mGreen, 255);
        mBlue  = (uint8_t)std::min((int16_t)mBlue  + other.mBlue,  255);
        mAlpha = (uint8_t)std::min((int16_t)mAlpha + other.mAlpha, 255);

        return *this;
    }

    Color Color::operator-(const Color& other) const
    {
        Color result;

        result.mRed   = (uint8_t)std::max((int16_t)mRed   - other.mRed,   0);
        result.mGreen = (uint8_t)std::max((int16_t)mGreen - other.mGreen, 0);
        result.mBlue  = (uint8_t)std::max((int16_t)mBlue  - other.mBlue,  0);
        result.mAlpha = (uint8_t)std::max((int16_t)mAlpha - other.mAlpha, 0);

        return result;
    }

    Color& Color::operator-=(const Color& other)
    {
        mRed   = (uint8_t)std::max((int16_t)mRed   - other.mRed,   0);
        mGreen = (uint8_t)std::max((int16_t)mGreen - other.mGreen, 0);
        mBlue  = (uint8_t)std::max((int16_t)mBlue  - other.mBlue,  0);
        mAlpha = (uint8_t)std::max((int16_t)mAlpha - other.mAlpha, 0);

        return *this;
    }

    Color Color::operator*(const Color& other) const
    {
        Color result;

        result.mRed   = (uint8_t)((int16_t)mRed   * other.mRed   / 255);
        result.mGreen = (uint8_t)((int16_t)mGreen * other.mGreen / 255);
        result.mBlue  = (uint8_t)((int16_t)mBlue  * other.mBlue  / 255);
        result.mAlpha = (uint8_t)((int16_t)mAlpha * other.mAlpha / 255);

        return result;
    }

    Color& Color::operator*=(const Color& other)
    {
        mRed   = (uint8_t)((int16_t)mRed * other.mRed     / 255);
        mGreen = (uint8_t)((int16_t)mGreen * other.mGreen / 255);
        mBlue  = (uint8_t)((int16_t)mBlue * other.mBlue   / 255);
        mAlpha = (uint8_t)((int16_t)mAlpha * other.mAlpha / 255);

        return *this;
    }

    Color Color::operator/(const Color& other) const     
    {
        Color result;

        if(other.mRed == 0)
            result.mRed = 255;
        else
        {
            float tempRed = ((float)mRed / 255.0f) / ((float)other.mRed / 255.0f);
            tempRed = std::min(tempRed, 1.0f);
            result.mRed = (uint8_t)(tempRed * 255.0f);
        }

        if(other.mGreen == 0)
            result.mGreen = 255;
        else
        {
            float tempGreen = ((float)mGreen / 255.0f) / ((float)other.mGreen / 255.0f);
            tempGreen = std::min(tempGreen, 1.0f);
            result.mGreen = (uint8_t)(tempGreen * 255.0f);
        }

        if(other.mBlue == 0)
            result.mBlue = 255;
        else
        {
            float tempBlue = ((float)mBlue / 255.0f) / ((float)other.mBlue / 255.0f);
            tempBlue = std::min(tempBlue, 1.0f);
            result.mBlue = (uint8_t)(tempBlue * 255.0f);
        }

        if(other.mAlpha == 0)
            result.mAlpha = 255;
        else
        {
            float tempAlpha = ((float)mAlpha / 255.0f) / ((float)other.mAlpha / 255.0f);
            tempAlpha = std::min(tempAlpha, 1.0f);
            result.mAlpha = (uint8_t)(tempAlpha * 255.0f);
        }

        return result;
    }

    Color& Color::operator/=(const Color& other)
    {
        if(other.mRed == 0)
            mRed = 255;
        else
        {
            float tempRed = ((float)mRed / 255.0f) / ((float)other.mRed / 255.0f);
            tempRed = std::min(tempRed, 1.0f);
            mRed = (uint8_t)(tempRed * 255.0f);
        }

        if(other.mGreen == 0)
            mGreen = 255;
        else
        {
            float tempGreen = ((float)mGreen / 255.0f) / ((float)other.mGreen / 255.0f);
            tempGreen = std::min(tempGreen, 1.0f);
            mGreen = (uint8_t)(tempGreen * 255.0f);
        }

        if(other.mBlue == 0)
            mBlue = 255;
        else
        {
            float tempBlue = ((float)mBlue / 255.0f) / ((float)other.mBlue / 255.0f);
            tempBlue = std::min(tempBlue, 1.0f);
            mBlue = (uint8_t)(tempBlue * 255.0f);
        }

        if(other.mAlpha == 0)
            mAlpha = 255;
        else
        {
            float tempAlpha = ((float)mAlpha / 255.0f) / ((float)other.mAlpha / 255.0f);
            tempAlpha = std::min(tempAlpha, 1.0f);
            mAlpha = (uint8_t)(tempAlpha * 255.0f);
        }

        return *this;
    }

    bool Color::operator==(const Color& other) const
    {
        return (mRed   == other.mRed  ) &&
               (mGreen == other.mGreen) &&
               (mBlue  == other.mBlue ) &&
               (mAlpha == other.mAlpha);
    }

    bool Color::operator!=(const Color& other) const
    {
        return !((mRed   == other.mRed  ) &&
                 (mGreen == other.mGreen) &&
                 (mBlue  == other.mBlue ) &&
                 (mAlpha == other.mAlpha));
    }


    uint8_t Color::r() const
    {
        return mRed;
    }

    uint8_t Color::g() const
    {
        return mGreen;
    }

    uint8_t Color::b() const
    {
        return mBlue;
    }

    uint8_t Color::a() const
    {
        return mAlpha;
    }

    float Color::rAsFloat() const
    {
		return (float)mRed / 255.0f;
    }

    float Color::gAsFloat() const
    {
		return (float)mGreen / 255.0f;
    }

    float Color::bAsFloat() const
    {
		return (float)mBlue / 255.0f;
    }

    float Color::aAsFloat() const
    {
		return (float)mAlpha / 255.0f;
    }

    void Color::setR(int32_t r)
    {
        mRed = std::max(0, std::min(255, r));
    }

    void Color::setG(int32_t g)
    {
        mGreen = std::max(0, std::min(255, g));
    }

    void Color::setB(int32_t b)
    {
        mBlue = std::max(0, std::min(255, b));
    }

    void Color::setA(int32_t a)
    {
        mAlpha = std::max(0, std::min(255, a));
    }

    void Color::setRAsFloat(float r)
    {
        mRed = (uint8_t)(std::max(0.0f, std::min(1.0f, r)) * 255.0f);
    }

    void Color::setGAsFloat(float g)
    {
        mGreen = (uint8_t)(std::max(0.0f, std::min(1.0f, g)) * 255.0f);
    }

    void Color::setBAsFloat(float b)
    {
        mBlue = (uint8_t)(std::max(0.0f, std::min(1.0f, b)) * 255.0f);
    }

    void Color::setAAsFloat(float a)
    {
        mAlpha = (uint8_t)(std::max(0.0f, std::min(1.0f, a)) * 255.0f);
    }

    const Color Color::Black(1, 0, 0); 
    const Color Color::Gray(128, 128, 128);
    const Color Color::White(255, 255, 255);
    const Color Color::Transparent(0, 0, 0, 0);
    const Color Color::Red(255, 0, 0); 
    const Color Color::Green(0, 255, 0); 
    const Color Color::Blue(0, 0, 255);
    const Color Color::Yellow(255, 255, 0); 
    const Color Color::Magenta(255, 0, 255);
    const Color Color::Cyan(0, 255, 255);
    const Color Color::Pink(255, 192, 203);
    const Color Color::Brown(157, 97, 42);
    const Color Color::Tan(210, 180, 140);
    const Color Color::Orange(255, 165, 0);
    const Color Color::Teal(0, 128, 128);
    const Color Color::Purple(128, 0, 128);
}
