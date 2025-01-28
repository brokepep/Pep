#include "peppch.h"
#include "Application.h"


namespace Pep {

	Application::Application() {
		m_Window = std::unique_ptr<Window>( Window::Create() );
		m_Window->SetEventCallback( BIND_EVENT_FN( Application::OnEvent ) );
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
	}

	void Application::PushOverlay( Layer* overlay ) {
		m_LayerStack.PushOverlay( overlay );
	}

	bool Application::OnWindowClose( WindowCloseEvent& e ) {
		m_Running = false;
		return true;
	}


}
