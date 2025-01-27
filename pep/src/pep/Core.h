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