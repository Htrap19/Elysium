#pragma once

#include "core/utility.h"

namespace Elysium
{
	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual uint32_t GetColorAttachmentId() const = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		static Shared<FrameBuffer> Create(uint32_t width, uint32_t height);
	};
}