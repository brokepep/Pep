#pragma once

#include "Pep/Core/Layer.h"

#include "Pep/Events/MouseEvent.h"
#include "Pep/Events/KeyEvent.h"
#include "Pep/Events/ApplicationEvent.h"

namespace Pep {
	class PEP_API ImGuiLayer : public Layer
	{
	private:
		float m_Time = 0.0f;

	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	};
}