#include <Pep.h>

class ExampleLayer : public Pep::Layer
{
public:
	ExampleLayer()
		: Layer( "Example" ) {
	}
	void OnUpdate() override {
		PEP_INFO( "ExampleLayer::Update" );
	}
	void OnEvent( Pep::Event& event ) override {
		PEP_TRACE( "{0}", event.ToString() );
	}
};

class Sandbox : public Pep::Application
{
public:
	Sandbox() {
		PushLayer( new ExampleLayer() );
	}
	~Sandbox() {
	}

};

Pep::Application* Pep::CreateApplication() {
	return new Sandbox();
}