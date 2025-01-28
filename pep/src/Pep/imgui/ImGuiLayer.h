#pragma once

#include "Pep/Layer.h"

#include "Pep/Events/MouseEvent.h"
#include "Pep/Events/KeyEvent.h"
#include "Pep/Events/ApplicationEvent.h"

namespace Pep {
	class PEP_API ImGuiLayer : public Layer
	{
	private:
		float m_Time = 0.0f;

		bool OnMouseButtonPressedEvent( MouseButtonPressedEvent& e );
		bool OnMouseButtonReleasedEvent( MouseButtonReleasedEvent& e );
		bool OnMouseMovedEvent( MouseMovedEvent& e );
		bool OnMouseScrolledEvent( MouseScrolledEvent& e );
		bool OnKeyPressedEvent( KeyPressedEvent& e );
		bool OnKeyReleasedEvent( KeyReleasedEvent& e );
		bool OnKeyTypedEvent( KeyTypedEvent& e );
		bool OnWindowResizeEvent( WindowResizeEvent& e );
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent( Event& event ) override;

	};
}