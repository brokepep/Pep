#pragma once

#include "Pep/Layer.h"

namespace Pep {
	class PEP_API ImGuiLayer : public Layer
	{
	private:
		float m_Time = 0.0f;
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent( Event& event ) override;

	};
}