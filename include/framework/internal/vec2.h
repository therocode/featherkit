#pragma once

namespace windbreeze
{
    template <class T>

    struct Vec2
    {
        T x;
        T y;
    };

    using UIntVec2 = Vec2<uint32_t>;
    using IntVec2 = Vec2<int32_t>;
    using FloatVec2 = Vec2<float>;
    using DoubleVec2 = Vec2<double>;
}
