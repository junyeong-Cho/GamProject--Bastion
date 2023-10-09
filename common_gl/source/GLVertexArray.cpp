/*
  Written: Junyeong Cho
  Date   : 9/09/2023
*/

#include "GLVertexArray.h"
#include "glcheck.h"  



GLVertexArray::GLVertexArray(GLPrimitive::Type the_primitive_pattern)
{
    glCheck(glCreateVertexArrays(1, &vertex_array_handle));
    primitive_pattern = the_primitive_pattern;
}


GLVertexArray::~GLVertexArray()
{
    glCheck(glDeleteVertexArrays(1, &vertex_array_handle));
}


GLVertexArray::GLVertexArray(GLVertexArray&& temp) noexcept
{
    std::swap(vertex_array_handle, temp.vertex_array_handle);
    std::swap(vertex_buffers, temp.vertex_buffers);
    std::swap(index_buffer, temp.index_buffer);
    std::swap(num_indices, temp.num_indices);
    std::swap(indices_type, temp.indices_type);
    std::swap(primitive_pattern, temp.primitive_pattern);
    std::swap(num_vertices, temp.num_vertices);
}


GLVertexArray& GLVertexArray::operator=(GLVertexArray&& temp) noexcept
{
    std::swap(vertex_array_handle, temp.vertex_array_handle);
    std::swap(vertex_buffers, temp.vertex_buffers);
    std::swap(index_buffer, temp.index_buffer);
    std::swap(num_indices, temp.num_indices);
    std::swap(indices_type, temp.indices_type);
    std::swap(primitive_pattern, temp.primitive_pattern);
    std::swap(num_vertices, temp.num_vertices);

    return *this;
}

void GLVertexArray::Use(bool bind) const
{
    glCheck(glBindVertexArray(bind ? vertex_array_handle : 0));
}

void GLVertexArray::AddVertexBuffer(GLVertexBuffer&& vertex_buffer, std::initializer_list<GLAttributeLayout> buffer_layout)
{
    for (const auto& attribute : buffer_layout)
    {
        glCheck(glEnableVertexArrayAttrib(vertex_array_handle, attribute.vertex_layout_location));
        glCheck(glVertexArrayVertexBuffer(vertex_array_handle, attribute.vertex_layout_location, vertex_buffer.GetHandle(), attribute.offset, attribute.stride));
        glCheck(glVertexArrayAttribFormat(vertex_array_handle, attribute.vertex_layout_location, attribute.component_dimension, attribute.component_type, attribute.normalized, attribute.relative_offset));
        glCheck(glVertexArrayAttribBinding(vertex_array_handle, attribute.vertex_layout_location, attribute.vertex_layout_location));
    }
    vertex_buffers.emplace_back(std::move(vertex_buffer));
}

void GLVertexArray::SetIndexBuffer(GLIndexBuffer&& the_indices)
{

    num_indices = the_indices.GetCount();
	indices_type = the_indices.GetElementType();
	glCheck(glVertexArrayElementBuffer(vertex_array_handle, the_indices.GetHandle()));
	index_buffer = std::move(the_indices);
}

void GLDrawIndexed(const GLVertexArray& vertex_array) noexcept
{
    vertex_array.Use();
    glCheck(glDrawElements(vertex_array.GetPrimitivePattern(), vertex_array.GetIndicesCount(), vertex_array.GetIndicesType(), nullptr));

}

void GLDrawVertices(const GLVertexArray& vertex_array) noexcept
{
    vertex_array.Use();
    glCheck(glDrawArrays(vertex_array.GetPrimitivePattern(), 0, vertex_array.GetVertexCount()));
}
