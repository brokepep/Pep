#pragma once

#include "Core.h"

#include "Window.h"
#include "Pep/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Pep/ImGui/ImGuiLayer.h"
//#include "Platform/OpenGL/OpenGLShader.h"
#include "Pep/Renderer/Shader.h"
#include "Pep/Renderer/Buffer.h"


namespace Pep {


	class PEP_API Application
	{
	private:
		bool OnWindowClose( WindowCloseEvent& e );

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;

		LayerStack m_LayerStack;

		uint m_VertexArray;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

		static Application* s_Instance;
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent( Event& e );

		void PushLayer( Layer* layer );
		void PushOverlay( Layer* overlay );

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}