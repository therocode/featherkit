namespace fea
{
    enum UniformType{FLOAT, VEC2, VEC3};

    class Uniform
    {
        private:
            uint8_t index;
            UniformType type;
            union
            {
                float floatVal;
                glm::vec2 vec2Val;
                glm::vec3 vec3Val;
            }
    };
}
