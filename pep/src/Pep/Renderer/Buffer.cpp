#include "peppch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Pep {

	Ref<VertexBuffer> VertexBuffer::Create( float* vertices, uint32_t size ) {
		switch( Renderer::GetAPI() )
		{
			case RendererAPI::API::None: PEP_CORE_ASSERT( false, "RendererAPI::None is currently not supported!" ); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>( vertices, size );
		}

		PEP_CORE_ASSERT( false, "Unknown RendererAPI!" );
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create( uint* indices, uint32_t count ) {
		switch( Renderer::GetAPI() )
		{
			case RendererAPI::API::None: PEP_CORE_ASSERT( false, "RendererAPI::None is currently not supported!" ); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared < OpenGLIndexBuffer>( indices, count );
		}

		PEP_CORE_ASSERT( false, "Unknown RendererAPI!" );
		return nullptr;
	}

}