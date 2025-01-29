#include "peppch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Pep {

	OpenGLContext::OpenGLContext( GLFWwindow* windowHandle ): m_WindowHandle( windowHandle ) {
		PEP_CORE_ASSERT( windowHandle, "Window handle is null!" );
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent( m_WindowHandle );
		int status = gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress );
		PEP_CORE_ASSERT( status, "Failed to initialize glad!" );

		PEP_CORE_INFO( "OpenGL Info:" );
		PEP_CORE_INFO( "    Version: {0}", ( const char* )glGetString( GL_VERSION ) );
		PEP_CORE_INFO( "    GPU: {0}", ( const char* )glGetString( GL_RENDERER ) );
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers( m_WindowHandle );
	}

}