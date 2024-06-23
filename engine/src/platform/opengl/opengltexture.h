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

		virtual uint32_t GetWidth() const override
		{ return m_Width; }
		virtual uint32_t GetHeight() const override
		{ return m_Height; }
		virtual uint32_t GetComponents() const override
		{ return m_Components; }

		virtual void SetData(const void* data, size_t size) override;

		virtual const std::string& GetPath() const override
		{ return m_Path; }

	private:
		uint32_t m_Id;
		uint32_t m_Width = 0, m_Height = 0, m_Components = 0;
		uint32_t m_InternalFormat, m_DataFormat;
		std::string m_Path;
	};

	class OpenGLCubeMap : public CubeMap
	{
	public:
		OpenGLCubeMap(const std::array<std::string, 6>& faces);
		~OpenGLCubeMap();

		virtual void Bind(uint32_t slot) override;

		virtual uint32_t GetWidth() const override
		{ return m_Width; }
		virtual uint32_t GetHeight() const override
		{ return m_Height; }
		virtual uint32_t GetComponents() const override
		{ return m_Components; }

		virtual void SetData(const void* data, size_t size) override;

		virtual const std::array<std::string, 6>& GetFaces() const override
		{ return m_Faces; }

	private:
		uint32_t m_Id;
		uint32_t m_Width = 0, m_Height = 0, m_Components = 0;
		uint32_t m_InternalFormat, m_DataFormat;
		std::array<std::string, 6> m_Faces;
	};
}