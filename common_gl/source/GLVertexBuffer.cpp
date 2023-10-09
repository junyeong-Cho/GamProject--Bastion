/*
  Written: Junyeong Cho
  Date   : 9/09/2023
*/

#include "GLVertexBuffer.h"
#include <glCheck.h>

GLVertexBuffer::GLVertexBuffer(GLsizei size_in_bytes) : size(size_in_bytes)
{

	glGenBuffers(1, &buffer_handle);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_handle);
	glNamedBufferStorage(buffer_handle, size_in_bytes, nullptr, GL_DYNAMIC_STORAGE_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glCheck(glGetError());
}

GLVertexBuffer::GLVertexBuffer(GLVertexBuffer&& temp) noexcept
{
	buffer_handle = temp.buffer_handle;
	size = temp.size;

	temp.buffer_handle = 0;
	temp.size = 0;
}

GLVertexBuffer::~GLVertexBuffer()
{
	glDeleteBuffers(1, &buffer_handle);
}


GLVertexBuffer& GLVertexBuffer::operator=(GLVertexBuffer&& temp) noexcept
{
	if (this != &temp)
	{
		glDeleteBuffers(1, &buffer_handle);

		buffer_handle = temp.buffer_handle;
		size = temp.size;

		temp.buffer_handle = 0;
		temp.size = 0;
	}

	glCheck(glGetError());
	return *this;
}

void GLVertexBuffer::Use(bool bind) const
{
	if (bind == true)
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer_handle);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glCheck(glGetError());

}

void GLVertexBuffer::send_buffer_data_to_gpu(const void* data, GLsizei size_bytes, GLsizei starting_offset) const
{
	Use();
	glBufferSubData(GL_ARRAY_BUFFER, starting_offset, size_bytes, data);
	glCheck(glGetError());

}

