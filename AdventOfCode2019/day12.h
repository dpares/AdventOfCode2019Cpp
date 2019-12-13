#pragma once

#include "dailychallenge.h"

class Day12 : public DailyChallenge
{
protected:
	virtual const char* GetInputSourceFile() const override { return "input/day12.txt"; }

	virtual void ChallengeA() override;
	virtual void ChallengeB() override;

private:
	struct Vector3
	{
		int m_X = 0;
		int m_Y = 0;
		int m_Z = 0;

		Vector3() = default;
		Vector3(int x, int y, int z) : m_X(x), m_Y(y), m_Z(z) {};
		void operator+=(const Vector3& other) { m_X += other.m_X; m_Y += other.m_Y; m_Z += other.m_Z; }
	};

	struct MoonInfo
	{
		Vector3 m_Position;
		Vector3 m_Velocity;

		MoonInfo(Vector3 position) : m_Position(position), m_Velocity() {}
	};

	void ParseInput();
	void CalculateNextTimeStep();
	int GetTotalSystemEnergy() const;

private:
	std::vector<MoonInfo> m_MoonInfoList;
};