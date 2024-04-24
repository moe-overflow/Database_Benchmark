#pragma once

#include <vector>
#include <string>
#include "utility/randomizer.hpp"
#include "utility/timer.hpp"

namespace Database_Benchmark
{
	class benchmark
	{
		virtual void run() = 0;
	};
}
