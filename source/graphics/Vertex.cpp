#include "ndrpch.h"
#include "Vertex.h"

namespace NDR
{
    // VertexAttribute
    VertexAttribute::VertexAttribute():
        _count(1),
        _normalized(false)
    {
    }

    VertexAttribute::VertexAttribute(GLuint count, bool normalized):
        _count(count),
        _normalized(normalized)
    {
    }

    uint32_t VertexAttribute::GetCount() const { return _count; }
    bool VertexAttribute::IsNormalized() const { return _normalized; }
    uint32_t VertexAttribute::GetStride() const { return _count * sizeof(float); }

    VertexLayout::VertexLayout():
        _stride(0)
    {
    }

    // VertexLayout
    VertexLayout::VertexLayout(const std::vector<VertexAttribute>& attributes):
        _attributes(attributes),
        _stride(0)
    {
        for (auto attribute : _attributes)
            _stride += attribute.GetStride();
    }

    VertexAttribute& VertexLayout::operator[](int32_t index) { return GetAttribute(index); }

    uint32_t VertexLayout::GetStride() const { return _stride; }
    VertexAttribute& VertexLayout::GetAttribute(int32_t index) { return _attributes[index]; }
    
    VertexLayout& VertexLayout::AddAttribute(const VertexAttribute& attribute)
    {
        _attributes.emplace_back(attribute);
        _stride += attribute.GetStride();
        return *this;
    }
    
    uint32_t VertexLayout::GetAttributeCount() const { return (uint32_t)_attributes.size(); }

    VertexArray::VertexArray():
        _id(0)
    {
    }

    VertexArray::VertexArray(VertexBuffer&& vertexBuffer, const VertexLayout& layout):
        _id(0),
        _vertexBuffer(std::move(vertexBuffer)),
        _layout(layout)
    {
        // create vertex array object
        glCreateVertexArrays(1, &_id);
        glBindVertexArray(_id);

        _vertexBuffer.Bind();

        // setup vertex attributes
        auto offset = 0;
        for(uint32_t attributeIndex = 0; attributeIndex < _layout.GetAttributeCount(); attributeIndex++)
        {
            VertexAttribute attribute = _layout[attributeIndex];
            glEnableVertexAttribArray(attributeIndex);
            glVertexAttribPointer(
                attributeIndex,
                attribute.GetCount(),
                GL_FLOAT,
                attribute.IsNormalized(),
                _layout.GetStride(),
                (const void*)offset);
            offset += attribute.GetStride();
        }
    }

    VertexArray::~VertexArray() { glDeleteVertexArrays(1, &_id); }

    VertexArray::VertexArray(VertexArray&& other) noexcept:
        _id(other._id),
        _vertexBuffer(std::move(other._vertexBuffer)),
        _layout(other._layout)
    {
        other._id = 0;
    }

    VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
    {
        if(*this != other)
        {
            _id = other._id;
            _vertexBuffer = std::move(other._vertexBuffer);
            _layout = other._layout;

            other._id = 0;
        }
        return *this;
    }

    VertexBuffer& VertexArray::GetVertexBuffer() { return _vertexBuffer; }
    VertexLayout& VertexArray::GetVertexLayout() { return _layout; }

    const VertexBuffer& VertexArray::GetVertexBuffer() const { return _vertexBuffer; }
    size_t VertexArray::GetVertexCount() const { return _vertexBuffer.GetCount(); }
    void VertexArray::Bind() const { glBindVertexArray(_id); }

    bool operator==(const VertexArray& left, const VertexArray& right) { return left._id == right._id; }
    bool operator!=(const VertexArray& left, const VertexArray& right) { return !(left == right); }
}
