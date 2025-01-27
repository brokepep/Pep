#pragma once

#ifdef PEP_PLATFORM_WINDOWS

extern Pep::Application* Pep::CreateApplication();

int main( int argc, char** argv ) {

	Pep::Log::Init();
	PEP_CORE_WARN( "Initialized Log!" );
	PEP_INFO( "Welcome To Pep!" );

	auto app = Pep::CreateApplication();
	app->Run();
	delete app;
}

#endif
