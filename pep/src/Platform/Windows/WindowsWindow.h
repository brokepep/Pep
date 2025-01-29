#pragma once

#include "Pep/Window.h"
#include "Pep/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Pep {
	class WindowsWindow : public Window
	{
	private:
		virtual void Init( const WindowProps& props );
		virtual void Shutdown();
		GLFWwindow* m_Window;
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallBack;
		};

		GraphicsContext* m_Context;

		WindowData m_Data;
	public:
		WindowsWindow( const WindowProps& props );
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline virtual void* GetNativeWindow() const {
			return m_Window;
		}

		//Window Attributes
		inline void SetEventCallback( const EventCallbackFn& callback ) override { m_Data.EventCallBack = callback; }
		void SetVSync( bool enabled ) override;
		bool IsVSync() const override;
	};
}