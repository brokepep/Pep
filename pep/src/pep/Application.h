#pragma once

#include "Core.h"
#include "Window.h"
#include "Pep/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"


namespace Pep {

	class PEP_API Application
	{
	private:
		bool OnWindowClose( WindowCloseEvent& e );
		std::unique_ptr<Window> m_Window;

		bool m_Running = true;
		LayerStack m_LayerStack;
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent( Event& e );
		void PushLayer( Layer* layer );
		void PushOverlay( Layer* overlay );

	};

	//To be defined in CLIENT
	Application* CreateApplication();

}