#include "pch.h"

#include "day1.h"

int Day1::RequiredFuel(int mass)
{
	return std::max(0, static_cast<int>(mass / 3.0f) - 2);
}

void Day1::ChallengeA()
{
	int moduleMass = 0;
	int fuelSum = 0;

	while (m_Input >> moduleMass)
	{
		const int moduleFuel = RequiredFuel(moduleMass);
		fuelSum += moduleFuel;
	}

	std::cout << "Challenge A result: " << fuelSum << std::endl;
}

void Day1::ChallengeB()
{
	int moduleMass = 0;
	int fuelSum = 0;

	while (m_Input >> moduleMass)
	{
		int moduleFuel = RequiredFuel(moduleMass);
		while (moduleFuel > 0)
		{
			fuelSum += moduleFuel;
			moduleFuel = RequiredFuel(moduleFuel);
		}
	}

	std::cout << "Challenge B result: " << fuelSum << std::endl;
}


