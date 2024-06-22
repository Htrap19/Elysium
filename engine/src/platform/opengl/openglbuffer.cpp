#include "openglbuffer.h"

#include <glad/glad.h>

namespace Elysium
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size, const void* data)
	{
		glGenBuffers(1, &m_Id);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_Id);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data,
									 size_t size,
									 size_t offset)
	{
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}

	/*
	* =========================================================================
	*/

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t count, const uint32_t* data)
		: m_Count(count)
	{
		glGenBuffers(1, &m_Id);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					 (count * sizeof(uint32_t)),
					 data,
					 GL_STREAM_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_Id);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLIndexBuffer::SetData(const uint32_t* data,
									uint32_t count,
									uint32_t offset)
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
						(offset * sizeof(uint32_t)),
						(count * sizeof(uint32_t)),
						data);
	}
}