#include "openglframebuffer.h"

#include <glad/glad.h>

namespace Elysium
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(uint32_t width, uint32_t height)
		: m_Width(width),
		m_Height(height)
	{
		CreateFrameBuffer();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		DeleteFrameBuffer();
	}

	void OpenGLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
	}

	void OpenGLFrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		m_Width = width;
		m_Height = height;
		DeleteFrameBuffer();
		CreateFrameBuffer();
	}

	void OpenGLFrameBuffer::CreateFrameBuffer()
	{
		glGenFramebuffers(1, &m_Id);
		Bind();

		glGenTextures(1, &m_ColorAttachmentId);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachmentId, 0);

		glGenTextures(1, &m_DepthStencilId);
		glBindTexture(GL_TEXTURE_2D, m_DepthStencilId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Width, m_Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthStencilId, 0);

		//Unbind();
	}

	void OpenGLFrameBuffer::DeleteFrameBuffer()
	{
		glDeleteTextures(1, &m_ColorAttachmentId);
		glDeleteFramebuffers(1, &m_Id);
	}
}