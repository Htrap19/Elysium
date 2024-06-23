#include "opengltexture.h"

#include "core/log.h"

#include <glad/glad.h>

#include <stb_image.h>

namespace Elysium
{
	namespace Util
	{
		static uint32_t CreateTexture2D(uint32_t width,
										uint32_t height,
										GLenum internalFormat,
										GLenum dataFormat,
										void* data)
		{
			uint32_t textureId;

			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBindTexture(GL_TEXTURE_2D, 0);

			return textureId;
		}

		static uint32_t CreateTextureCubeMap(const std::array<std::string, 6>& faces,
											 GLenum internalFormat,
											 GLenum dataFormat,
											 void* data)
		{
			uint32_t textureId;
			

			return textureId;
		}
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& imgFile, bool flip)
		: m_Path(imgFile)
	{
		stbi_set_flip_vertically_on_load(flip);

		int width, height, components;
		stbi_uc* data = stbi_load(imgFile.c_str(), &width, &height, &components, 0);
		if (!data)
		{
			ES_CORE_ERROR("Unable to load {0} texture", imgFile.c_str());
			stbi_image_free(data);
			return;
		}

		m_Width = width;
		m_Height = height;
		m_Components = components;

		m_InternalFormat = GL_RED, m_DataFormat = GL_RED;
		if (components == 3)
			m_InternalFormat = GL_RGB8, m_DataFormat = GL_RGB;
		else if (components == 4)
			m_InternalFormat = GL_RGBA8, m_DataFormat = GL_RGBA;

		m_Id = Util::CreateTexture2D(width, height, (GLenum)m_InternalFormat, (GLenum)m_DataFormat, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
		m_Id = Util::CreateTexture2D(width, height, (GLenum)m_InternalFormat, (GLenum)m_DataFormat, nullptr);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_Id);
	}

	void OpenGLTexture2D::Bind(uint32_t slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_Id);
	}

	void OpenGLTexture2D::SetData(const void* data, size_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		if (size != (m_Width * m_Height * bpp))
		{
			ES_CORE_ERROR("Entire texture must be loaded!");
			return;
		}

		glBindTexture(GL_TEXTURE_2D, m_Id);
		glTexImage2D(GL_TEXTURE_2D, 0, (GLenum)m_InternalFormat, m_Width, m_Height, 0, (GLenum)m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	OpenGLCubeMap::OpenGLCubeMap(const std::array<std::string, 6>& faces)
		: m_Faces(faces)
	{
		glGenTextures(1, &m_Id);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_Id);

		int width, height, components;
		for (uint32_t i = 0; i < faces.size(); i++)
		{
			stbi_uc* data = stbi_load(faces[i].c_str(), &width, &height, &components, 0);
			if (data)
			{
				m_InternalFormat = GL_RED, m_DataFormat = GL_RED;
				if (components == 3)
					m_InternalFormat = GL_RGB8, m_DataFormat = GL_RGB;
				else if (components == 4)
					m_InternalFormat = GL_RGBA8, m_DataFormat = GL_RGBA;

				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
							 0,
							 m_InternalFormat,
							 width,
							 height,
							 0,
							 m_DataFormat,
							 GL_UNSIGNED_BYTE,
							 data);
				stbi_image_free(data);
			}
			else
			{
				ES_CORE_ERROR("Cubemap tex failed to load at path: {0}", faces[i]);
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	OpenGLCubeMap::~OpenGLCubeMap()
	{
		glDeleteTextures(1, &m_Id);
	}

	void OpenGLCubeMap::Bind(uint32_t slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_Id);
	}

	void OpenGLCubeMap::SetData(const void* data, size_t size)
	{
		for (uint32_t i = 0; i < m_Faces.size(); i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						 0,
						 m_InternalFormat,
						 m_Width,
						 m_Height,
						 0,
						 m_DataFormat,
						 GL_UNSIGNED_BYTE,
						 data);
		}
	}
}