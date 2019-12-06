#include "pch.h"

#include "challengefactory.h"
#include "dailychallenge.h"

int main()
{
	std::unique_ptr<DailyChallenge> dailyChallenge;
	unsigned int desiredDay;

	while (dailyChallenge == nullptr)
	{
		std::cout << "Please pick a day in the range [1,25]: ";
		std::cin >> desiredDay;

		dailyChallenge = ChallengeFactory::GetChallengeForDay(desiredDay);
	}

	std::cout << std::endl << std::endl;

	dailyChallenge->Execute();
}