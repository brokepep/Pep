#pragma once

#include "Pep/Core.h"
#include "Pep/Events/Event.h"

namespace Pep {
	class PEP_API Layer
	{
	protected:
		std::string m_DebugName;
	public:
		Layer( const std::string& name = "Layer" );


		virtual ~Layer();
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent( Event& event ) {}

		inline const std::string& GetName() const { return m_DebugName; }
	};
}

