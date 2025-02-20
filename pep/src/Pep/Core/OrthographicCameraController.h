#pragma once

#include <glm/glm.hpp>
#include "Pep/Core/Timestep.h"
#include "Pep/Renderer/OrthographicCamera.h"
#include "Pep/Events/ApplicationEvent.h"
#include "Pep/Events/MouseEvent.h"


namespace Pep {
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController( float aspectRatio, bool rotation = false );

		void OnUpdate( Timestep ts );
		void OnEvent( Event& e );

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseScrolled( MouseScrolledEvent& e );
		bool OnWindowResized( WindowResizeEvent& e );
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation = false;

		glm::vec3 m_CameraPosition = glm::vec3( 0.0f );
		float m_CameraRotation = 0.f;
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;
	};
}
