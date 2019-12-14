#include "pch.h"

#include "day12.h"

#include <numeric>

namespace
{
	int CompareInt(int lhs, int rhs)
	{
		int result = 0;

		if (lhs < rhs)
		{
			result = 1;
		}
		else if (lhs > rhs)
		{
			result = -1;
		}

		return result;
	}
}

void Day12::ParseInput()
{
	m_MoonInfoList.clear();

	m_MoonInfoList.emplace_back(MoonInfo({ -9,-1,-1 }));
	m_MoonInfoList.emplace_back(MoonInfo({ 2,9,5 }));
	m_MoonInfoList.emplace_back(MoonInfo({ 10,18,-12 }));
	m_MoonInfoList.emplace_back(MoonInfo({ -6,15,-7 }));
}

void Day12::CalculateNextTimeStep()
{
	for (int i = 0; i < m_MoonInfoList.size(); ++i)
	{
		MoonInfo& currentMI = m_MoonInfoList[i];

		for (int j = 0; j < m_MoonInfoList.size(); ++j)
		{
			if (i == j)
			{
				continue;
			}

			const MoonInfo& otherMI = m_MoonInfoList[j];

			Vector3 velocityInc;
			velocityInc.m_X = CompareInt(currentMI.m_Position.m_X, otherMI.m_Position.m_X);
			velocityInc.m_Y = CompareInt(currentMI.m_Position.m_Y, otherMI.m_Position.m_Y);
			velocityInc.m_Z = CompareInt(currentMI.m_Position.m_Z, otherMI.m_Position.m_Z);

			currentMI.m_Velocity += velocityInc;
		}
	}

	for (int i = 0; i < m_MoonInfoList.size(); ++i)
	{
		MoonInfo& currentMI = m_MoonInfoList[i];
		currentMI.m_Position += currentMI.m_Velocity;
	}
}

int Day12::GetTotalSystemEnergy() const
{
	int systemEnergy = 0;

	for (const auto& moonInfo : m_MoonInfoList)
	{
		const int potentialEnergy = std::abs(moonInfo.m_Position.m_X) + std::abs(moonInfo.m_Position.m_Y) + 
			std::abs(moonInfo.m_Position.m_Z);
		const int kineticEnergy = std::abs(moonInfo.m_Velocity.m_X) + std::abs(moonInfo.m_Velocity.m_Y) +
			std::abs(moonInfo.m_Velocity.m_Z);

		systemEnergy += potentialEnergy * kineticEnergy;
	}

	return systemEnergy;
}

void Day12::ChallengeA()
{
	ParseInput();

	for (int i = 0; i < 1000; ++i)
	{
		CalculateNextTimeStep();
	}

	std::cout << "Challenge A result: " << GetTotalSystemEnergy() << std::endl;
}

void Day12::ChallengeB()
{
	ParseInput();

	constexpr unsigned long long MAX_VALUE = std::numeric_limits<unsigned long long>::max();
	Vector3<unsigned long long> cycleSteps{ MAX_VALUE, MAX_VALUE, MAX_VALUE };

	std::vector<MoonInfo> originalState;
	originalState.reserve(m_MoonInfoList.size());
	for (const auto& moonInfo : m_MoonInfoList)
	{
		originalState.emplace_back(moonInfo);
	}

	unsigned long long currentStep = 0;
	while (cycleSteps.m_X == MAX_VALUE || cycleSteps.m_Y == MAX_VALUE || cycleSteps.m_Z == MAX_VALUE)
	{
		++currentStep;
		CalculateNextTimeStep();

		Vector3 differentComponents;
		for (int i = 0; i < m_MoonInfoList.size(); ++i)
		{
			const Vector3<int>& newVelocity = m_MoonInfoList[i].m_Velocity;
			const Vector3<int>& newPosition = m_MoonInfoList[i].m_Position;
			const Vector3<int>& originalPosition = originalState[i].m_Position;

			if (newVelocity.m_X != 0 || newPosition.m_X != originalPosition.m_X)
			{
				++differentComponents.m_X;
			}
			if (newVelocity.m_Y != 0 || newPosition.m_Y != originalPosition.m_Y)
			{
				++differentComponents.m_Y;
			}
			if (newVelocity.m_Z != 0 || newPosition.m_Z != originalPosition.m_Z)
			{
				++differentComponents.m_Z;
			}
		}

		if (cycleSteps.m_X == MAX_VALUE && differentComponents.m_X == 0)
		{
			cycleSteps.m_X = currentStep;
		}
		if (cycleSteps.m_Y == MAX_VALUE && differentComponents.m_Y == 0)
		{
			cycleSteps.m_Y = currentStep;
		}
		if (cycleSteps.m_Z == MAX_VALUE && differentComponents.m_Z == 0)
		{
			cycleSteps.m_Z = currentStep;
		}
	}

	std::cout << "Challenge B result: " << LeastCommonMultiplier(cycleSteps) << std::endl;
}


