#pragma once

#include "Pep/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Pep {
	class OpenGLContext : public GraphicsContext
	{
	private:
		GLFWwindow* m_WindowHandle;
	public:
		OpenGLContext( GLFWwindow* windowHandle );

		virtual void Init() override;
		virtual void SwapBuffers() override;
	};
}

