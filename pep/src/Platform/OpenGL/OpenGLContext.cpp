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

		#ifdef PEP_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv( GL_MAJOR_VERSION, &versionMajor );
		glGetIntegerv( GL_MINOR_VERSION, &versionMinor );
		PEP_CORE_ASSERT( versionMajor > 4 || ( versionMajor == 4 && versionMinor >= 5 ), "Hazel requires at least OpenGL version 4.5!" );
		#endif
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers( m_WindowHandle );
	}

}