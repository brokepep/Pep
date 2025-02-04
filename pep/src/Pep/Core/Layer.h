#pragma once

#include "Pep/Core/Core.h"
#include "Pep/Events/Event.h"
#include "Pep/Core/Timestep.h"

namespace Pep {
	class PEP_API Layer
	{
	protected:
		std::string m_DebugName;
	public:
		Layer( const std::string& name = "Layer" );
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate( Timestep ts ) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent( Event& event ) {}

		inline const std::string& GetName() const { return m_DebugName; }
	};
}

