#include "peppch.h"
#include "Application.h"

#include "Pep/Log.h"

#include "Input.h"
#include "KeyCodes.h"
#include "Pep/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Pep {
	Application* Application::s_Instance = nullptr;


	Application::Application() {
		PEP_ASSERT( !s_Instance, "Application already exists!" );
		s_Instance = this;

		m_Window = std::unique_ptr<Window>( Window::Create() );
		m_Window->SetEventCallback( PEP_BIND_EVENT_FN( Application::OnEvent ) );

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay( m_ImGuiLayer );
	}

	Application::~Application() {
	}

	void Application::Run() {
		while( m_Running )
		{
			float time = ( float )glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for( Layer* layer : m_LayerStack )
				layer->OnUpdate( timestep );

			m_ImGuiLayer->Begin();
			for( Layer* layer : m_LayerStack )
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent( Event& e ) {
		EventDispatcher dispatcher( e );
		dispatcher.Dispatch<WindowCloseEvent>( PEP_BIND_EVENT_FN( Application::OnWindowClose ) );
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
