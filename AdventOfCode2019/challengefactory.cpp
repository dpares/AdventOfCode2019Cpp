#include "pch.h"

#include "challengefactory.h"
#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"


std::unique_ptr<DailyChallenge> ChallengeFactory::GetChallengeForDay(unsigned int day)
{
	std::unique_ptr<DailyChallenge> challenge = nullptr;

	switch (day)
	{
		case 1:
		{
			challenge = std::make_unique<Day1>();
			break;
		}
		case 2:
		{
			challenge = std::make_unique<Day2>();
			break;
		}
		case 3:
		{
			challenge = std::make_unique<Day3>();
			break;
		}
		case 4:
		{
			challenge = std::make_unique<Day4>();
			break;
		}
	}

	return std::move(challenge);
}