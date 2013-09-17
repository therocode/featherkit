namespace fea
{
    struct RenderInfo
    {
        std::vector<Uniform> uniforms;
        std::vector<VertexAttribute> vertexAttributes;
        BlendMode blendMode;
        GLenum drawMode;
    }
}
