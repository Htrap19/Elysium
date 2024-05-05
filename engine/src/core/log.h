#pragma once

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#include "utility.h"

namespace Elysium
{
	class Log
	{
	public:
		static void Init();

		inline static Shared<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
		inline static Shared<spdlog::logger> GetClientLogger() { return s_ClientLogger; }

	private:
		static Shared<spdlog::logger> s_CoreLogger;
		static Shared<spdlog::logger> s_ClientLogger;
	};
}

#define ES_CORE_TRACE(...)		::Elysium::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ES_CORE_INFO(...)		::Elysium::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ES_CORE_WARN(...)		::Elysium::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ES_CORE_ERROR(...)		::Elysium::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ES_CORE_CRITICAL(...)	::Elysium::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define ES_TRACE(...)		::Elysium::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ES_INFO(...)		::Elysium::Log::GetClientLogger()->info(__VA_ARGS__)
#define ES_WARN(...)		::Elysium::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ES_ERROR(...)		::Elysium::Log::GetClientLogger()->error(__VA_ARGS__)
#define ES_CRITICAL(...)	::Elysium::Log::GetClientLogger()->critical(__VA_ARGS__)
