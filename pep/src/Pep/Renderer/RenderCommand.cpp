#include "peppch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Pep {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}