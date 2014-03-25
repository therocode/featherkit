namespace std
{
    template<>
    struct hash<fea::Font>
    {
        public:
            std::size_t operator()(fea::Font const& font) const 
            {
                std::size_t h1 = std::hash<std::string>()(font.getPath());
                std::size_t h2 = std::hash<uint32_t>()((uint32_t)(font.getSize() * 100.0f));
                return h1 ^ (h2 << 1);
            }
    };
}
