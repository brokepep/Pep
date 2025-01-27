#pragma once

#ifdef PEP_PLATFORM_WINDOWS
#ifdef PEP_BUILD_DLL
#define PEP_API __declspec(dllexport)
#else
#define PEP_API __declspec(dllimport)
#endif
#else
#error pep only supports Windows!
#endif

#ifdef PEP_ENABLE_ASSERTS
#define PEP_ASSERT(x, ...) { if(!(x)) { PEP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define PEP_CORE_ASSERT(x, ...) { if(!(x)) { PEP_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define PEP_ASSERT(x, ...)
#define PEP_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)