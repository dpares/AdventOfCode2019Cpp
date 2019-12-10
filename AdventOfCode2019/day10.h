#pragma once

#include "dailychallenge.h"

class Day10 : public DailyChallenge
{
protected:
	virtual const char* GetInputSourceFile() const override { return "input/day10.txt"; }

	virtual void ChallengeA() override;
	virtual void ChallengeB() override;

private:
	using AsteroidMapRow = std::vector<char>;
	using AsteroidMap = std::vector<AsteroidMapRow>;
	using Coordinates = std::pair<int, int>;

	struct DestructionInfo
	{
		Coordinates m_Coordinates;
		float m_Angle;
		int m_Distance;

		bool operator<(const DestructionInfo& other) const;
		bool operator==(const DestructionInfo& other) const;
	};

	void ParseAsteroidMap();

	int GreatestCommonDivisor(int x, int y) const;
	float GetAngleBetweenPoints(Coordinates lhs, Coordinates rhs) const;
	int GetSquaredDistanceBetweenPoints(Coordinates lhs, Coordinates rhs) const;

	int GetAsteroidsInLOS(int originX, int originY);
	Coordinates GetNthDestroyedAsteroidPosition(int n) const;
	

private:
	AsteroidMap m_Map;
	Coordinates m_BestLocation;
};