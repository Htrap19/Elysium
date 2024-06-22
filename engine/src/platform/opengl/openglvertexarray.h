#pragma once

#include "renderer/vertexarray.h"

namespace Elysium
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Shared<VertexBuffer>& buffer) override;
		virtual void SetIndexBuffer(const Shared<IndexBuffer>& buffer) override;

		virtual const std::vector<Shared<VertexBuffer>> GetVertexBuffers() const override
		{ return m_VertexBuffers; }

		virtual Shared<IndexBuffer> GetIndexBuffer() const override
		{ return m_IndexBuffer; }

	private:
		uint32_t m_Id;
		std::vector<Shared<VertexBuffer>> m_VertexBuffers;
		Shared<IndexBuffer> m_IndexBuffer;
		uint32_t m_AttribIndex = 0;
	};
}