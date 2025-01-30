#include "peppch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Pep {

	static GLenum ShaderDataTypeToGLBaseType( ShaderDataType type ) {
		switch( type )
		{
			case Pep::ShaderDataType::Float:	return GL_FLOAT;
				break;
			case Pep::ShaderDataType::Float2:	return GL_FLOAT;
				break;
			case Pep::ShaderDataType::Float3:	return GL_FLOAT;
				break;
			case Pep::ShaderDataType::Float4:	return GL_FLOAT;
				break;
			case Pep::ShaderDataType::Mat3:		return GL_FLOAT;
				break;
			case Pep::ShaderDataType::Mat4:		return GL_FLOAT;
				break;
			case Pep::ShaderDataType::Int:		return GL_INT;
				break;
			case Pep::ShaderDataType::Int2:		return GL_INT;
				break;
			case Pep::ShaderDataType::Int3:		return GL_INT;
				break;
			case Pep::ShaderDataType::Int4:		return GL_INT;
				break;
			case Pep::ShaderDataType::Bool:		return GL_BOOL;
				break;
			default:
				{
					PEP_CORE_ASSERT( false, "Unknown ShaderDataType!" );
					return 0;
				}
				break;
		}
	}


	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays( 1, &m_RendererID );
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray( m_RendererID );
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray( 0 );
	}

	void OpenGLVertexArray::AddVertexBuffer( const std::shared_ptr<VertexBuffer>& vertexBuffer ) {
		glBindVertexArray( m_RendererID );
		vertexBuffer->Bind();
		uint32_t index = 0;
		PEP_CORE_ASSERT( vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!" );
		for( const auto& element : vertexBuffer->GetLayout() )
		{
			glEnableVertexAttribArray( index );
			glVertexAttribPointer( index,
								   element.GetComponentCount(),
								   ShaderDataTypeToGLBaseType( element.Type ),
								   element.Normalized ? GL_TRUE : GL_FALSE,
								   vertexBuffer->GetLayout().GetStride(),
								   ( const void* )element.Offset );
			index++;
		}
		m_VertexBuffers.push_back( vertexBuffer );
	}

	void OpenGLVertexArray::SetIndexBuffer( const std::shared_ptr<IndexBuffer>& indexBuffer ) {
		glBindVertexArray( m_RendererID );
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}