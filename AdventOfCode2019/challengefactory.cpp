#include "pch.h"

#include "challengefactory.h"
#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day5.h"
#include "day6.h"
#include "day7.h"
#include "day8.h"
#include "day9.h"
#include "day10.h"
#include "day11.h"
#include "day12.h"
#include "day13.h"

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
		case 5:
		{
			challenge = std::make_unique<Day5>();
			break;
		}
		case 6:
		{
			challenge = std::make_unique<Day6>();
			break;
		}
		case 7:
		{
			challenge = std::make_unique<Day7>();
			break;
		}
		case 8:
		{
			challenge = std::make_unique<Day8>();
			break;
		}
		case 9:
		{
			challenge = std::make_unique<Day9>();
			break;
		}
		case 10:
		{
			challenge = std::make_unique<Day10>();
			break;
		}
		case 11:
		{
			challenge = std::make_unique<Day11>();
			break;
		}
		case 12:
		{
			challenge = std::make_unique<Day12>();
			break;
		}
		case 13:
		{
			challenge = std::make_unique<Day13>();
			break;
		}
	}

	return std::move(challenge);
}