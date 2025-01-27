#pragma once

#ifdef PEP_PLATFORM_WINDOWS

extern Pep::Application* Pep::CreateApplication();

int main(int argc, char** argv)
{
    auto app = Pep::CreateApplication();
    app->Run();
    delete app;
}

#endif
