#pragma once

#include "Pep.h"

class Sandbox2D : public Pep::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate( Pep::Timestep ts ) override;
	virtual void OnImGuiRender() override;
	void OnEvent( Pep::Event& e ) override;

private:
	Pep::OrthographicCameraController m_CameraController;

	// Temp
	Pep::Ref<Pep::VertexArray> m_SquareVA;
	Pep::Ref<Pep::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 0.8f };
};

