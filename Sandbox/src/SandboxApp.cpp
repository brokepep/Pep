#include <Pep.h>

class Sandbox : public Pep::Application {
public:
    Sandbox()
    {
    }
    ~Sandbox()
    {
    }

};

Pep::Application* Pep::CreateApplication()
{
    return new Sandbox();
}