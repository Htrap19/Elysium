#include "openglvertexarray.h"

#include "core/log.h"

#include <glad/glad.h>

namespace Elysium
{
	namespace Util
	{
		static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
				return GL_FLOAT;
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
				return GL_INT;
			case ShaderDataType::Bool:
				return GL_BOOL;

			default:
				break;
			}

			return GL_NONE;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_Id);
		Bind();
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_Id);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_Id);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Shared<VertexBuffer>& buffer)
	{
		Bind();
		buffer->Bind();

		auto& layout = buffer->GetLayout();
		for (auto& element : layout)
		{
			switch (element.Type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				glEnableVertexAttribArray(m_AttribIndex);
				glVertexAttribPointer(m_AttribIndex,
					element.GetComponentCount(),
					Util::ShaderDataTypeToOpenGLType(element.Type),
					GL_FALSE,
					(GLsizei)layout.GetStride(),
					(const void*)element.Offset);
				m_AttribIndex++;
				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			{
				glEnableVertexAttribArray(m_AttribIndex);
				glVertexAttribIPointer(m_AttribIndex,
					element.GetComponentCount(),
					Util::ShaderDataTypeToOpenGLType(element.Type),
					(GLsizei)layout.GetStride(),
					(const void*)element.Offset);
				m_AttribIndex++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
				ES_CORE_ERROR("Mat3/Mat4 currrently not supported as layout attributes!");

			default:
				break;
			}
		}

		m_VertexBuffers.push_back(buffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Shared<IndexBuffer>& buffer)
	{
		Bind();
		buffer->Bind();
		m_IndexBuffer = buffer;
	}

}
