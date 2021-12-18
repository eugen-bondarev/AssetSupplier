#include "Time.h"

#include <chrono>

namespace Asu
{
	Time CastTime(const std::chrono::system_clock::duration duration)
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(
			duration
		).count();
	}

	Time GetTime()
	{
		return CastTime(std::chrono::system_clock::now().time_since_epoch());
	}
}