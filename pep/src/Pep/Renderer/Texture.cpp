#include "peppch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Pep {
	Ref<Texture2D> Texture2D::Create( const std::string& path ) {
		switch( Renderer::GetAPI() )
		{
			case RendererAPI::API::None: PEP_CORE_ASSERT( false, "RendererAPI::None is currently not supported!" ); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>( path );
		}
		PEP_CORE_ASSERT( false, "Unknown RendererAPI!" );
		return nullptr;
	}
}