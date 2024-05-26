#pragma once

#include "renderer/texture.h"

namespace Elysium
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& imgFile, bool flip = true);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		~OpenGLTexture2D();

		virtual void Bind(uint32_t slot) override;

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetComponents() const override { return m_Components; }

		virtual void SetData(const void* data, size_t size) override;

	private:
		uint32_t m_Id;
		uint32_t m_Width = 0, m_Height = 0, m_Components = 0;
		uint32_t m_InternalFormat, m_DataFormat;
	};
}