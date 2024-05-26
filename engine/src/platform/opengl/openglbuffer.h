#pragma once

#include "renderer/buffer.h"

namespace Elysium
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(size_t size, const void* data = nullptr);
		~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override
		{ m_Layout = layout; }
		virtual void SetData(const void* data,
							 size_t size,
							 size_t offset = 0) override;
		virtual const BufferLayout& GetLayout() const override
		{ return m_Layout; }

	private:
		uint32_t m_Id = 0;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t count, const uint32_t* data = nullptr);
		~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return m_Count; }
		virtual void SetData(const uint32_t* data,
							 uint32_t count,
							 uint32_t offset = 0) override;

	private:
		uint32_t m_Id = 0;
		uint32_t m_Count = 0;
	};
}