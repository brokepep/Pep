#pragma once

#include "Core.h"

#include "Window.h"
#include "Pep/Core/LayerStack.h"
#include "Pep/Events/Event.h"
#include "Pep/Events/ApplicationEvent.h"

#include "Pep/Core/Timestep.h"

#include "Pep/ImGui/ImGuiLayer.h"

namespace Pep {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent( Event& e );

		void PushLayer( Layer* layer );
		void PushOverlay( Layer* layer );

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose( WindowCloseEvent& e );
		bool OnWindowResize( WindowResizeEvent& e );
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}