#include "peppch.h"
#include "WindowsWindow.h"

#include "Pep/Events/ApplicationEvent.h"
#include "Pep/Events/MouseEvent.h"
#include "Pep/Events/KeyEvent.h"

#include <glad/glad.h>

namespace Pep {
	static bool s_GLFWInitialized = false;

	static void GLFW_Error_Callback( int error, const char* description ) {
		PEP_CORE_ERROR( "GLFW Error ({0}): {1}", error, description );
	}

	Window* Window::Create( const WindowProps& props ) {
		return new WindowsWindow( props );
	}

	WindowsWindow::WindowsWindow( const WindowProps& props ) {
		Init( props );
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init( const WindowProps& props ) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		PEP_CORE_INFO( "Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height );

		if( !s_GLFWInitialized )
		{
			int success = glfwInit();
			PEP_CORE_ASSERT( success, "Could not initialize GLFW!" );
			glfwSetErrorCallback( GLFW_Error_Callback );
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow( ( int )props.Width, ( int )props.Height, m_Data.Title.c_str(), nullptr, nullptr );
		glfwMakeContextCurrent( m_Window );
		int status = gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress );
		PEP_CORE_ASSERT( status, "Failed to initialize glad!" );
		glfwSetWindowUserPointer( m_Window, &m_Data );
		SetVSync( true );

		//GLFW callbacks
		glfwSetWindowSizeCallback( m_Window, []( GLFWwindow* window, int width, int height ) {
			WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );

			WindowResizeEvent event( width, height );

			data.Width = width;
			data.Height = height;
			data.EventCallBack( event );

		} );

		glfwSetWindowCloseCallback( m_Window, []( GLFWwindow* window ) {
			WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );
			WindowCloseEvent event;
			data.EventCallBack( event );
		} );

		glfwSetKeyCallback( m_Window, []( GLFWwindow* window, int key, int scancode, int action, int mods ) {
			WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );

			switch( action )
			{
				case GLFW_PRESS:
					{
						KeyPressedEvent event( key, 1 );
						data.EventCallBack( event );
						break;
					}
				case GLFW_RELEASE:
					{
						KeyReleasedEvent event( key );
						data.EventCallBack( event );
						break;
					}
				case GLFW_REPEAT:
					{
						KeyPressedEvent event( key, 0 );
						data.EventCallBack( event );
						break;
					}
			}
		} );

		glfwSetMouseButtonCallback( m_Window, []( GLFWwindow* window, int button, int action, int mods ) {
			WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );
			switch( action )
			{
				case GLFW_PRESS:
					{
						MouseButtonPressedEvent event( button );
						data.EventCallBack( event );
						break;
					}
				case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event( button );
						data.EventCallBack( event );
						break;
					}
			}
		} );

		glfwSetScrollCallback( m_Window, []( GLFWwindow* window, double xOffset, double yOffset ) {
			WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );

			MouseScrolledEvent event( ( float )xOffset, ( float )yOffset );
			data.EventCallBack( event );
		} );

		glfwSetCursorPosCallback( m_Window, []( GLFWwindow* window, double xPos, double yPos ) {
			WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );

			MouseMovedEvent event( ( float )xPos, ( float )yPos );
			data.EventCallBack( event );
		} );


	}
	void WindowsWindow::Shutdown() {
		glfwDestroyWindow( m_Window );
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers( m_Window );
	}

	void WindowsWindow::SetVSync( bool enabled ) {
		if( enabled )

			glfwSwapInterval( 1 );
		else
			glfwSwapInterval( 0 );

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}
}