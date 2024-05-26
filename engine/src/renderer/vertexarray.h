#pragma once

#include "renderer/buffer.h"

namespace Elysium
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Shared<VertexBuffer>& buffer) = 0;
		virtual void SetIndexBuffer(const Shared<IndexBuffer>& buffer) = 0;

		static Shared<VertexArray> Create();
	};
}