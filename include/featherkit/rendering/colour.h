#pragma once
#include <stdint.h>
#include <algorithm>

namespace fea
{
    class Colour
    {
        public:
            Colour();
            Colour(float r, float g, float b, float a = 1.0f);
            Colour(int32_t r, int32_t g, int32_t b, int32_t a = 255);
            Colour(int32_t hexValue, float a);
            Colour(int32_t hexValue, int32_t a = 255);

            Colour operator+(const Colour& other) const;
            Colour& operator+=(const Colour& other);
            Colour operator-(const Colour& other) const;
            Colour& operator-=(const Colour& other);
            Colour operator*(const Colour& other) const;
            Colour& operator*=(const Colour& other);
            Colour operator/(const Colour& other) const;
            Colour& operator/=(const Colour& other);
            bool operator==(const Colour& other) const;
            bool operator!=(const Colour& other) const;

            float r() const;
            float g() const;
            float b() const;
            float a() const;

            uint8_t rAsByte() const;
            uint8_t gAsByte() const;
            uint8_t bAsByte() const;
            uint8_t aAsByte() const;

        private:
            float red;
            float green;
            float blue;
            float alpha;
    };
}
