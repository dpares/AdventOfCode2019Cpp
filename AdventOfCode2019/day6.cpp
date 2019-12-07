#include "pch.h"

#include "day6.h"

namespace
{
	constexpr int NAME_LENGTH = 4;
}

int Day6::FindOrCreateOrbitObject(std::string name)
{
	int objectIndex = 0;

	const auto& orbittedIt = std::find_if(m_OrbitList.begin(), m_OrbitList.end(),
		[name](const OrbitObject& object) {return name == object.m_Name; });

	if (orbittedIt == m_OrbitList.end())
	{
		m_OrbitList.emplace_back(name);
		objectIndex = m_OrbitList.size() - 1;
	}
	else
	{
		objectIndex = std::distance(m_OrbitList.begin(), orbittedIt);
	}

	return objectIndex;
}

void Day6::ParseOrbitTree()
{
	m_OrbitList.clear();

	char objectName[NAME_LENGTH];
	while (m_Input.good())
	{
		if (m_Input.get(objectName, NAME_LENGTH))
		{
			int orbittedIdx = FindOrCreateOrbitObject(objectName);

			m_Input.ignore();
			if (m_Input.get(objectName, NAME_LENGTH))
			{
				int orbittingIdx = FindOrCreateOrbitObject(objectName);
				m_OrbitList[orbittingIdx].m_OrbittingIdx = orbittedIdx;

				m_OrbitList[orbittedIdx].m_OrbittedBy.emplace_back(orbittingIdx);

				m_Input.ignore();
			}
		}
	}
}

int Day6::GetNumOrbitsForObject(int orbitIdx, std::vector<int>& orbitsPerNode) const
{
	int numOrbits = 0;

	if (orbitsPerNode[orbitIdx] != -1)
	{
		numOrbits = orbitsPerNode[orbitIdx];
	}
	else
	{
		const int nextOrbitIdx = m_OrbitList[orbitIdx].m_OrbittingIdx;
		if (nextOrbitIdx != -1)
		{
			numOrbits = numOrbits + 1 + GetNumOrbitsForObject(nextOrbitIdx, orbitsPerNode);
		}

		orbitsPerNode[orbitIdx] = numOrbits;
	}

	return numOrbits;
}

int Day6::GetTotalNumOrbits() const
{
	int totalOrbits = 0;

	std::vector<int> orbitsPerNode(m_OrbitList.size(), -1);

	for (int orbitIdx = 0; orbitIdx < m_OrbitList.size(); ++orbitIdx)
	{
		totalOrbits += GetNumOrbitsForObject(orbitIdx, orbitsPerNode);
	}

	return totalOrbits;
}

void Day6::ChallengeA()
{
	ParseOrbitTree();

	std::cout << "Challenge A result: " << GetTotalNumOrbits() << std::endl;
}

unsigned int Day6::GetMinPathLength(int origin, int dest, std::vector<int>& visitedNodes) const
{
	unsigned int minLength = 0;
	if (origin == dest)
	{
		return minLength;
	}
	else
	{
		minLength = -1;

		const auto& nodeIt = std::find(visitedNodes.cbegin(), visitedNodes.cend(), origin);
		if (nodeIt != visitedNodes.cend())
		{
			return minLength;
		}
		else
		{
			visitedNodes.emplace_back(origin);

			unsigned int pathLength = 0;

			const int orbittingIdx = m_OrbitList[origin].m_OrbittingIdx;
			if (orbittingIdx != -1)
			{
				pathLength = GetMinPathLength(orbittingIdx, dest, visitedNodes);
				if (pathLength != -1)
				{
					++pathLength;
				}

				if (pathLength < minLength)
				{
					minLength = pathLength;
				}
			}

			for (const int& orbittedIdx : m_OrbitList[origin].m_OrbittedBy)
			{
				pathLength = GetMinPathLength(orbittedIdx, dest, visitedNodes);
				if (pathLength != -1)
				{
					++pathLength;
				}

				if (pathLength < minLength)
				{
					minLength = pathLength;
				}
			}

			
		}

		
	}

	return minLength;
}

int Day6::GetMinTransfersToSanta()
{
	const int originIdx = FindOrCreateOrbitObject("YOU");
	const int destIdx = FindOrCreateOrbitObject("SAN");
	std::vector<int> visitedNodes;
	visitedNodes.reserve(m_OrbitList.size());

	return GetMinPathLength(m_OrbitList[originIdx].m_OrbittingIdx, m_OrbitList[destIdx].m_OrbittingIdx, visitedNodes);
}

void Day6::ChallengeB()
{
	ParseOrbitTree();

	std::cout << "Challenge B result: " << GetMinTransfersToSanta() << std::endl;
}
