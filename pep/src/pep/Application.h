#pragma once
#include "Core.h"

namespace Pep {

class PEP_API Application {
    public:
        Application();
        ~Application();
        void Run();
};

    Application* CreateApplication();

}