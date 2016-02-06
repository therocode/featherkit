#include <fea/rendering/color.hpp>
#include <algorithm>

namespace fea
{
    Color::Color()
    {
        r = 0u;
        g = 0u;
        b = 0u;
        a = 255u;
    }

    Color::Color(float _r, float _g, float _b, float _a)
    {
        r = (uint8_t)(std::max(0.0f, std::min(1.0f, _r)) * 255.0f);
        g = (uint8_t)(std::max(0.0f, std::min(1.0f, _g)) * 255.0f);
        b = (uint8_t)(std::max(0.0f, std::min(1.0f, _b)) * 255.0f);
        a = (uint8_t)(std::max(0.0f, std::min(1.0f, _a)) * 255.0f);
    }

    Color::Color(int32_t _r, int32_t _g, int32_t _b, int32_t _a)
    {
        r = std::max(0, std::min(255, _r));
        g = std::max(0, std::min(255, _g));
        b = std::max(0, std::min(255, _b));
        a = std::max(0, std::min(255, _a));
    }

    Color::Color(int32_t hexValue, float _a)
    {
        hexValue = std::max(0, std::min(0xFFFFFF, hexValue));

        r = (hexValue >> 16) & 0xFF;
        g = (hexValue >>  8) & 0xFF;
        b =  hexValue & 0xFF;
        a = (uint8_t)(std::max(0.0f, std::min(1.0f, _a)) * 255.0f);
    }

    Color::Color(int32_t hexValue, int32_t _a)
    {
        hexValue = std::max(0, std::min(0xFFFFFF, hexValue));

        r = (hexValue >> 16) & 0xFF;
        g = (hexValue >>  8) & 0xFF;
        b =  hexValue & 0xFF;
        a = std::max(0, std::min(255, _a));
    }

    Color Color::operator+(const Color& other) const
    {
        Color result;

        result.r = (uint8_t)std::min((int16_t)r + other.r, 255);
        result.g = (uint8_t)std::min((int16_t)g + other.g, 255);
        result.b = (uint8_t)std::min((int16_t)b + other.b, 255);
        result.a = (uint8_t)std::min((int16_t)a + other.a, 255);

        return result;
    }

    Color& Color::operator+=(const Color& other)
    {
        r = (uint8_t)std::min((int16_t)r + other.r, 255);
        g = (uint8_t)std::min((int16_t)g + other.g, 255);
        b = (uint8_t)std::min((int16_t)b + other.b, 255);
        a = (uint8_t)std::min((int16_t)a + other.a, 255);

        return *this;
    }

    Color Color::operator-(const Color& other) const
    {
        Color result;

        result.r = (uint8_t)std::max((int16_t)r - other.r, 0);
        result.g = (uint8_t)std::max((int16_t)g - other.g, 0);
        result.b = (uint8_t)std::max((int16_t)b - other.b, 0);
        result.a = (uint8_t)std::max((int16_t)a - other.a, 0);

        return result;
    }

    Color& Color::operator-=(const Color& other)
    {
        r = (uint8_t)std::max((int16_t)r - other.r, 0);
        g = (uint8_t)std::max((int16_t)g - other.g, 0);
        b = (uint8_t)std::max((int16_t)b - other.b, 0);
        a = (uint8_t)std::max((int16_t)a - other.a, 0);

        return *this;
    }

    Color Color::operator*(const Color& other) const
    {
        Color result;

        result.r = (uint8_t)((int16_t)r * other.r / 255);
        result.g = (uint8_t)((int16_t)g * other.g / 255);
        result.b = (uint8_t)((int16_t)b * other.b / 255);
        result.a = (uint8_t)((int16_t)a * other.a / 255);

        return result;
    }

    Color& Color::operator*=(const Color& other)
    {
        r = (uint8_t)((int16_t)r * other.r / 255);
        g = (uint8_t)((int16_t)g * other.g / 255);
        b = (uint8_t)((int16_t)b * other.b / 255);
        a = (uint8_t)((int16_t)a * other.a / 255);

        return *this;
    }

    Color Color::operator/(const Color& other) const     
    {
        Color result;

        if(other.r == 0)
            result.r = 255;
        else
        {
            float tempRed = ((float)r / 255.0f) / ((float)other.r / 255.0f);
            tempRed = std::min(tempRed, 1.0f);
            result.r = (uint8_t)(tempRed * 255.0f);
        }

        if(other.g == 0)
            result.g = 255;
        else
        {
            float tempGreen = ((float)g / 255.0f) / ((float)other.g / 255.0f);
            tempGreen = std::min(tempGreen, 1.0f);
            result.g = (uint8_t)(tempGreen * 255.0f);
        }

        if(other.b == 0)
            result.b = 255;
        else
        {
            float tempBlue = ((float)b / 255.0f) / ((float)other.b / 255.0f);
            tempBlue = std::min(tempBlue, 1.0f);
            result.b = (uint8_t)(tempBlue * 255.0f);
        }

        if(other.a == 0)
            result.a = 255;
        else
        {
            float tempAlpha = ((float)a / 255.0f) / ((float)other.a / 255.0f);
            tempAlpha = std::min(tempAlpha, 1.0f);
            result.a = (uint8_t)(tempAlpha * 255.0f);
        }

        return result;
    }

    Color& Color::operator/=(const Color& other)
    {
        if(other.r == 0)
            r = 255;
        else
        {
            float tempRed = ((float)r / 255.0f) / ((float)other.r / 255.0f);
            tempRed = std::min(tempRed, 1.0f);
            r = (uint8_t)(tempRed * 255.0f);
        }

        if(other.g == 0)
            g = 255;
        else
        {
            float tempGreen = ((float)g / 255.0f) / ((float)other.g / 255.0f);
            tempGreen = std::min(tempGreen, 1.0f);
            g = (uint8_t)(tempGreen * 255.0f);
        }

        if(other.b == 0)
            b = 255;
        else
        {
            float tempBlue = ((float)b / 255.0f) / ((float)other.b / 255.0f);
            tempBlue = std::min(tempBlue, 1.0f);
            b = (uint8_t)(tempBlue * 255.0f);
        }

        if(other.a == 0)
            a = 255;
        else
        {
            float tempAlpha = ((float)a / 255.0f) / ((float)other.a / 255.0f);
            tempAlpha = std::min(tempAlpha, 1.0f);
            a = (uint8_t)(tempAlpha * 255.0f);
        }

        return *this;
    }

    bool Color::operator==(const Color& other) const
    {
        return (r   == other.r  ) &&
               (g == other.g) &&
               (b  == other.b ) &&
               (a == other.a);
    }

    bool Color::operator!=(const Color& other) const
    {
        return !((r   == other.r  ) &&
                 (g == other.g) &&
                 (b  == other.b ) &&
                 (a == other.a));
    }

    float Color::rAsFloat() const
    {
		return (float)r / 255.0f;
    }

    float Color::gAsFloat() const
    {
		return (float)g / 255.0f;
    }

    float Color::bAsFloat() const
    {
		return (float)b / 255.0f;
    }

    float Color::aAsFloat() const
    {
		return (float)a / 255.0f;
    }

    void Color::setRAsFloat(float _r)
    {
        r = (uint8_t)(std::max(0.0f, std::min(1.0f, _r)) * 255.0f);
    }

    void Color::setGAsFloat(float _g)
    {
        g = (uint8_t)(std::max(0.0f, std::min(1.0f, _g)) * 255.0f);
    }

    void Color::setBAsFloat(float _b)
    {
        b = (uint8_t)(std::max(0.0f, std::min(1.0f, _b)) * 255.0f);
    }

    void Color::setAAsFloat(float _a)
    {
        a = (uint8_t)(std::max(0.0f, std::min(1.0f, _a)) * 255.0f);
    }

    const Color Color::Black(0, 0, 0); 
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
