#pragma once

class DailyChallenge;

class ChallengeFactory
{
public:
	static std::unique_ptr<DailyChallenge> GetChallengeForDay(unsigned int day);
};