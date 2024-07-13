#pragma once

#include "renderer/framebuffer.h"

namespace Elysium
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(uint32_t width, uint32_t height);
		~OpenGLFrameBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		inline
		virtual uint32_t GetWidth() const override
		{ return m_Width; }

		inline
		virtual uint32_t GetHeight() const override
		{ return m_Height; }

		inline
		virtual uint32_t GetColorAttachmentId() const override
		{ return m_ColorAttachmentId; }

		virtual void Resize(uint32_t width, uint32_t height) override;

	private:
		void CreateFrameBuffer();
		void DeleteFrameBuffer();

	private:
		uint32_t m_Id;
		uint32_t m_Width, m_Height;
		uint32_t m_ColorAttachmentId;
		uint32_t m_DepthStencilId;
	};
}