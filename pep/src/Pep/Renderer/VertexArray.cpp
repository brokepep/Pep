#include "peppch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Pep {
	Ref<VertexArray> VertexArray::Create() {
		switch( Renderer::GetAPI() )
		{
			case RendererAPI::API::None: PEP_CORE_ASSERT( false, "RendererAPI::None is currently not supported!" ); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_unique< OpenGLVertexArray>();
		}
		PEP_CORE_ASSERT( false, "Unknown RendererAPI!" );
		return nullptr;
	}

}