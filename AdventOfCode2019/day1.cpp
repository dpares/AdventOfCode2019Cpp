#include "pch.h"

int requiredFuel(int mass)
{
	return std::max(0, static_cast<int>(mass / 3.0f) - 2);
}

int challengeA(std::ifstream& input)
{
	int moduleMass = 0;
	int fuelSum = 0;

	while (input >> moduleMass)
	{
		const int moduleFuel = requiredFuel(moduleMass);
		fuelSum += moduleFuel;
	}

	return fuelSum;
}

int challengeB(std::ifstream& input)
{
	int moduleMass = 0;
	int fuelSum = 0;

	while (input >> moduleMass)
	{
		int moduleFuel = requiredFuel(moduleMass);
		while (moduleFuel > 0)
		{
			fuelSum += moduleFuel;
			moduleFuel = requiredFuel(moduleFuel);
		}
	}

	return fuelSum;
}

/*int main()
{
	std::ifstream input ("input/day1.txt", std::ifstream::in);

	int totalFuel = challengeA(input);
	std::cout << "Total fuel for challenge A: " << totalFuel << std::endl;

	input.clear();
	input.seekg(0);

	totalFuel = challengeB(input);
	std::cout << "Total fuel for challenge B: " << totalFuel << std::endl;
}*/


