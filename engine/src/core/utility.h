#pragma once

#include <memory>

namespace Elysium
{
	template <typename T>
	using Shared = std::shared_ptr<T>;

	template <typename T, typename ... Args>
	Shared<T> MakeShared(Args&& ... args)
	{
		return std::make_shared<T, Args...>(args...);
	}

	template <typename T>
	using Unique = std::unique_ptr<T>;

	template <typename T, typename ... Args>
	Unique<T> MakeUnique(Args&& ... args)
	{
		return std::make_unique<T, Args...>(args...);
	}
}

#define BIT(n) (1 << n)

#define ES_BIND_EVENT_FN(func) std::bind(&func, this, std::placeholders::_1)

#define ES_EXPAND(x) (x)