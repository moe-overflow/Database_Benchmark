#pragma once 

#include <vector>
#include <random>

namespace helper
{
	class randomizer
	{
	public:

		randomizer() {}

		// Generates a vector that is filled with random double values
		static std::vector<double> randomize(int limit)
		{
			std::vector<double> data;
			std::uniform_real_distribution<double> unif(0, 100);
			std::default_random_engine dre;
			for (int i = 0; i < limit; i++)
				data.push_back(unif(dre));
			return data;
		}



	};
	
}