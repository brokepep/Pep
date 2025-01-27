#include "peppch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"

namespace Pep {

	Application::Application() {
		m_Window = std::unique_ptr<Window>( Window::Create() );
	}

	Application::~Application() {
	}

	void Application::Run() {
		while( m_Running )
		{
			m_Window->OnUpdate();
		}
	}
}
