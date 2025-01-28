#include "peppch.h"
#include "Application.h"

#include <glad/glad.h>

namespace Pep {
	Application* Application::s_Instance = nullptr;

	Application::Application() {
		PEP_ASSERT( !s_Instance, "Application already exists!" );
		s_Instance = this;

		m_Window = std::unique_ptr<Window>( Window::Create() );
		m_Window->SetEventCallback( BIND_EVENT_FN( Application::OnEvent ) );

		unsigned int id;
		glGenVertexArrays( 1, &id );
	}

	Application::~Application() {
	}

	void Application::Run() {
		while( m_Running )
		{
			for( Layer* layer : m_LayerStack )
				layer->OnUpdate();
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent( Event& e ) {
		EventDispatcher dispatcher( e );
		dispatcher.Dispatch<WindowCloseEvent>( BIND_EVENT_FN( Application::OnWindowClose ) );
		//PEP_TRACE( "{0}", e.ToString() );

		for( auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			( *--it )->OnEvent( e );
			if( e.Handled )
				break;
		}
	}

	void Application::PushLayer( Layer* layer ) {
		m_LayerStack.PushLayer( layer );
		layer->OnAttach();
	}

	void Application::PushOverlay( Layer* overlay ) {
		m_LayerStack.PushOverlay( overlay );
		overlay->OnAttach();
	}

	bool Application::OnWindowClose( WindowCloseEvent& e ) {
		m_Running = false;
		return true;
	}


}
