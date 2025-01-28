#include <Pep.h>

class ExampleLayer : public Pep::Layer
{
public:
	ExampleLayer()
		: Layer( "Example" ) {
	}
	void OnUpdate() override {
		//PEP_INFO( "ExampleLayer::Update" );
	}
	void OnEvent( Pep::Event& event ) override {
		if( event.GetEventType() == Pep::EventType::KeyTyped )
		{
			Pep::KeyTypedEvent& e = ( Pep::KeyTypedEvent& )event;
			PEP_TRACE( "{0}", ( char )e.GetKeyCode() );
		}
	}
};

class Sandbox : public Pep::Application
{
public:
	Sandbox() {
		PushLayer( new ExampleLayer() );
		PushOverlay( new Pep::ImGuiLayer() );
	}
	~Sandbox() {
	}

};

Pep::Application* Pep::CreateApplication() {
	return new Sandbox();
}