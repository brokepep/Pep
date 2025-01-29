#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Pep {

	class PEP_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core Log Macros
#define PEP_CORE_ERROR(...)    ::Pep::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PEP_CORE_WARN(...)     ::Pep::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PEP_CORE_INFO(...)     ::Pep::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PEP_CORE_TRACE(...)    ::Pep::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PEP_CORE_FATAL(...)    ::Pep::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log Macros
#define PEP_ERROR(...)         ::Pep::Log::GetClientLogger()->error(__VA_ARGS__)
#define PEP_WARN(...)          ::Pep::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PEP_INFO(...)          ::Pep::Log::GetClientLogger()->info(__VA_ARGS__)
#define PEP_TRACE(...)         ::Pep::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PEP_FATAL(...)         ::Pep::Log::GetClientLogger()->fatal(__VA_ARGS__)


