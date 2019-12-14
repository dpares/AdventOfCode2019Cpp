#pragma once

#include "dailychallenge.h"

class Day12 : public DailyChallenge
{
protected:
	virtual const char* GetInputSourceFile() const override { return "input/day12.txt"; }

	virtual void ChallengeA() override;
	virtual void ChallengeB() override;

private:
	template <typename Type = int>
	struct Vector3
	{
		Type m_X = 0;
		Type m_Y = 0;
		Type m_Z = 0;

		Vector3() = default;
		Vector3(Type x, Type y, Type z) : m_X(x), m_Y(y), m_Z(z) {};
		void operator+=(const Vector3& other) { m_X += other.m_X; m_Y += other.m_Y; m_Z += other.m_Z; }
		bool operator==(const Vector3& other) const { return m_X == other.m_X && m_Y == other.m_Y && m_Z == other.m_Z; }
		bool operator!=(const Vector3& other) const { return operator==(other) == false; }
	};

	struct MoonInfo
	{
		Vector3<int> m_Position;
		Vector3<int> m_Velocity;

		MoonInfo(Vector3<int> position) : m_Position(position), m_Velocity() {}
	};

	void ParseInput();
	void CalculateNextTimeStep();
	int GetTotalSystemEnergy() const;

	template <typename Type = int>
	Type LeastCommonMultiplier(Vector3<Type> vector) const
	{
		return std::lcm(vector.m_X, std::lcm(vector.m_Y, vector.m_Z));
	}

private:
	std::vector<MoonInfo> m_MoonInfoList;
};