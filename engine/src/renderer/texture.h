#pragma once

#include "core/utility.h"

#include <string>

namespace Elysium
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void Bind(uint32_t slot = 0) = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetComponents() const = 0;

		virtual void SetData(const void* data, size_t size) = 0;

		virtual const std::string& GetPath() const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Shared<Texture2D> Create(const std::string& imgFile, bool flip = true);
		static Shared<Texture2D> Create(uint32_t width, uint32_t height);
	};
}