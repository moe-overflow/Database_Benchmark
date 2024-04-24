#pragma once 

#include <chrono>

namespace helper
{
	class timer
	{
	public:
		timer() : _start(std::chrono::high_resolution_clock::now()) {}
		void reset() { _start = std::chrono::high_resolution_clock::now(); }
		
		double elapsed() 
		{
			auto end = std::chrono::high_resolution_clock::now();
			return std::chrono::duration<double, std::milli>(end - _start).count();
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> _start;
	};
}