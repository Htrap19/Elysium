#pragma once

#include "renderer/vertexarray.h"

namespace Elysium
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const Shared<VertexBuffer>& buffer) override;
		void SetIndexBuffer(const Shared<IndexBuffer>& buffer) override;

	private:
		uint32_t m_Id;
		std::vector<Shared<VertexBuffer>> m_VertexBuffers;
		Shared<IndexBuffer> m_IndexBuffer;
		uint32_t m_AttribIndex = 0;
	};
}