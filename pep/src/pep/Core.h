#pragma once
#include <memory>

#ifdef PEP_PLATFORM_WINDOWS
#if PEP_DYNAMIC_LINK
#ifdef PEP_BUILD_DLL
#define PEP_API __declspec(dllexport)
#else
#define PEP_API __declspec(dllimport)
#endif
#else
#define PEP_API
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

#define PEP_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

typedef unsigned int uint;

namespace Pep {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}