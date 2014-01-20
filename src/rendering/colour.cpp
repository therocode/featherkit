#include <featherkit/rendering/colour.h>

namespace fea
{
    Colour::Colour()
    {
    }

    Colour::Colour(float r, float g, float b, float a)
    {
        red = std::max(0.0f, std::min(1.0f, r));
        green = std::max(0.0f, std::min(1.0f, g));
        blue = std::max(0.0f, std::min(1.0f, b));
        alpha = std::max(0.0f, std::min(1.0f, a));
    }

    Colour::Colour(int32_t r, int32_t g, int32_t b, int32_t a)
    {
        red = float(std::max(0, std::min(255, r)))/255.0f;
        green = float(std::max(0, std::min(255, g)))/255.0f;
        blue = float(std::max(0, std::min(255, b)))/255.0f;
        alpha = float(std::max(0, std::min(255, a)))/255.0f;
    }

    Colour::Colour(int32_t hexValue, float a)
    {
        hexValue = std::max(0, std::min(0xFFFFFF, hexValue));

        red = float((hexValue >> 16) & 0xFF)/255.0f;
        green = float((hexValue >> 8) & 0xFF)/255.0f;
        blue = float(hexValue & 0xFF)/255.0f;
        alpha = std::max(0.0f, std::min(1.0f, a));
    }

    Colour::Colour(int32_t hexValue, int32_t a)
    {
        hexValue = std::max(0, std::min(0xFFFFFF, hexValue));

        red = float((hexValue >> 16) & 0xFF)/255.0f;
        green = float((hexValue >> 8) & 0xFF)/255.0f;
        blue = float(hexValue & 0xFF)/255.0f;
        alpha = float(std::max(0, std::min(255, a)))/255.0f;
    }

    Colour Colour::operator+(const Colour& other) const
    {
        Colour result;

        result.red = red + other.red + 0.00196;
        result.green = green + other.green + 0.00196;
        result.blue = blue + other.blue + 0.00196;
        result.alpha = alpha + other.alpha + 0.00196;

        result.red = std::max(0.0f, std::min(1.0f, result.red));
        result.green = std::max(0.0f, std::min(1.0f, result.green));
        result.blue = std::max(0.0f, std::min(1.0f, result.blue));
        result.alpha = std::max(0.0f, std::min(1.0f, result.alpha));

        return result;
    }

    Colour& Colour::operator+=(const Colour& other)
    {
        red = red + other.red;
        green = green + other.green;
        blue = blue + other.blue;
        alpha = alpha + other.alpha;

        red = std::max(0.0f, std::min(1.0f, red));
        green = std::max(0.0f, std::min(1.0f, green));
        blue = std::max(0.0f, std::min(1.0f, blue));
        alpha = std::max(0.0f, std::min(1.0f, alpha));

        return *this;
    }

    Colour Colour::operator-(const Colour& other) const
    {
        Colour result;

        result.red = red - other.red + 0.00196;
        result.green = green - other.green + 0.00196;
        result.blue = blue - other.blue + 0.00196;
        result.alpha = alpha - other.alpha + 0.00196;

        result.red = std::max(0.0f, std::min(1.0f, result.red));
        result.green = std::max(0.0f, std::min(1.0f, result.green));
        result.blue = std::max(0.0f, std::min(1.0f, result.blue));
        result.alpha = std::max(0.0f, std::min(1.0f, result.alpha));

        return result;
    }

    Colour& Colour::operator-=(const Colour& other)
    {
        red = red - other.red;
        green = green - other.green;
        blue = blue - other.blue;
        alpha = alpha - other.alpha;

        red = std::max(0.0f, std::min(1.0f, red));
        green = std::max(0.0f, std::min(1.0f, green));
        blue = std::max(0.0f, std::min(1.0f, blue));
        alpha = std::max(0.0f, std::min(1.0f, alpha));

        return *this;
    }

    Colour Colour::operator*(const Colour& other) const
    {
        Colour result;

        result.red = red * other.red + 0.00196;
        result.green = green * other.green + 0.00196;
        result.blue = blue * other.blue + 0.00196;
        result.alpha = alpha * other.alpha + 0.00196;

        result.red = std::max(0.0f, std::min(1.0f, result.red));
        result.green = std::max(0.0f, std::min(1.0f, result.green));
        result.blue = std::max(0.0f, std::min(1.0f, result.blue));
        result.alpha = std::max(0.0f, std::min(1.0f, result.alpha));

        return result;
    }

    Colour& Colour::operator*=(const Colour& other)
    {
        red = red * other.red;
        green = green * other.green;
        blue = blue * other.blue;
        alpha = alpha * other.alpha;

        red = std::max(0.0f, std::min(1.0f, red));
        green = std::max(0.0f, std::min(1.0f, green));
        blue = std::max(0.0f, std::min(1.0f, blue));
        alpha = std::max(0.0f, std::min(1.0f, alpha));

        return *this;
    }

    Colour Colour::operator/(const Colour& other) const
    {
        Colour result;

        result.red = red / other.red + 0.00196;
        result.green = green / other.green + 0.00196;
        result.blue = blue / other.blue + 0.00196;
        result.alpha = alpha / other.alpha + 0.00196;

        result.red = std::max(0.0f, std::min(1.0f, result.red));
        result.green = std::max(0.0f, std::min(1.0f, result.green));
        result.blue = std::max(0.0f, std::min(1.0f, result.blue));
        result.alpha = std::max(0.0f, std::min(1.0f, result.alpha));

        return result;
    }

    Colour& Colour::operator/=(const Colour& other)
    {
        red = red / other.red;
        green = green / other.green;
        blue = blue / other.blue;
        alpha = alpha / other.alpha;

        red = std::max(0.0f, std::min(1.0f, red));
        green = std::max(0.0f, std::min(1.0f, green));
        blue = std::max(0.0f, std::min(1.0f, blue));
        alpha = std::max(0.0f, std::min(1.0f, alpha));

        return *this;
    }

    bool Colour::operator==(const Colour& other) const
    {
        uint8_t r = red * 255;
        uint8_t g = green * 255;
        uint8_t b = blue * 255;
        uint8_t a = alpha * 255;

        uint8_t r2 = other.red * 255;
        uint8_t g2 = other.green * 255;
        uint8_t b2 = other.blue * 255;
        uint8_t a2 = other.alpha * 255;

        return (r == r2) &&
               (b == b2) &&
               (g == g2) &&
               (a == a2);
    }

    bool Colour::operator!=(const Colour& other) const
    {
        uint8_t r = red * 255;
        uint8_t g = green * 255;
        uint8_t b = blue * 255;
        uint8_t a = alpha * 255;

        uint8_t r2 = other.red * 255;
        uint8_t g2 = other.green * 255;
        uint8_t b2 = other.blue * 255;
        uint8_t a2 = other.alpha * 255;

        return !((r == r2) &&
                 (b == b2) &&
                 (g == g2) &&
                 (a == a2));
    }


    float Colour::r()
    {
        return red;
    }

    float Colour::g()
    {
        return green;
    }

    float Colour::b()
    {
        return blue;
    }

    float Colour::a()
    {
        return alpha;
    }

    uint8_t Colour::rAsByte()
    {
        return red * 255;
    }

    uint8_t Colour::gAsByte()
    {
        return green * 255;
    }

    uint8_t Colour::bAsByte()
    {
        return blue * 255;
    }

    uint8_t Colour::aAsByte()
    {
        return alpha * 255;
    }
}
