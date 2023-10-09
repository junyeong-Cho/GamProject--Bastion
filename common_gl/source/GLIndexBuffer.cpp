/*
  Written: Junyeong Cho
  Date   : 9/09/2023
*/

#include "GLIndexBuffer.h"
#include <glCheck.h>

#include "GLIndexBuffer.h"

namespace
{
    void create_indices_buffer(GLHandle& handle, GLIndexElement::Type type, GLsizei count, const void* data)
    {
        glCreateBuffers(1, &handle);
        glNamedBufferStorage(handle, count * sizeof(type), data, 0);
    }
}

GLIndexBuffer::GLIndexBuffer(std::span<const unsigned int> indices)
{
    element_type = GLIndexElement::UInt;
    count = static_cast<GLsizei>(indices.size());
    create_indices_buffer(indices_handle, element_type, count, indices.data());

    glCheck(glGetError());

}

GLIndexBuffer::GLIndexBuffer(std::span<const unsigned short> indices)
{
    element_type = GLIndexElement::UShort;
    count = static_cast<GLsizei>(indices.size());
    create_indices_buffer(indices_handle, element_type, count, indices.data());

    glCheck(glGetError());

}

GLIndexBuffer::GLIndexBuffer(std::span<const unsigned char> indices)
{
    element_type = GLIndexElement::UByte;
    count = static_cast<GLsizei>(indices.size());
    create_indices_buffer(indices_handle, element_type, count, indices.data());

    glCheck(glGetError());

}

GLIndexBuffer::~GLIndexBuffer()
{
    if (indices_handle != 0)
    {
        glDeleteBuffers(1, &indices_handle);
    }
}

GLIndexBuffer::GLIndexBuffer(GLIndexBuffer&& temp) noexcept
{
    glDeleteBuffers(1, &indices_handle);

    indices_handle = temp.indices_handle;
    count = temp.count;
    element_type = temp.element_type;

    temp.indices_handle = 0;
    temp.count = 0;
    temp.element_type = GLIndexElement::None;
}

GLIndexBuffer& GLIndexBuffer::operator=(GLIndexBuffer&& temp) noexcept
{
    if (this != &temp)
    {
        // Ensure the current object's resources are deleted
        glDeleteBuffers(1, &indices_handle);

        // Move the resources
        indices_handle = temp.indices_handle;
        count = temp.count;
        element_type = temp.element_type;

        // Invalidate the temporary object
        temp.indices_handle = 0;
        temp.count = 0;
        temp.element_type = GLIndexElement::None;
    }

    // You can also call glCheck(glGetError()); here if needed
    glCheck(glGetError());
    return *this;
}


void GLIndexBuffer::Use(bool bind) const
{
    if (bind)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_handle);
    }
    else
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    glCheck(glGetError());

}

