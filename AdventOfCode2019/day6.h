#pragma once

#include "dailychallenge.h"

#include <string>
#include <vector>

class Day6 : public DailyChallenge
{
protected:
	virtual const char* GetInputSourceFile() const override { return "input/day6.txt"; }

	virtual void ChallengeA() override;
	virtual void ChallengeB() override;

private:
	struct OrbitObject
	{
		std::string m_Name;
		int m_OrbittingIdx;
		std::vector<int> m_OrbittedBy;

		OrbitObject() = default;
		OrbitObject(std::string name) : m_Name(name), m_OrbittingIdx(-1), m_OrbittedBy() {}
	};

	int FindOrCreateOrbitObject(std::string name);
	void ParseOrbitTree();

	int GetNumOrbitsForObject(int orbitIdx, std::vector<int>& orbitsPerNode) const;
	int GetTotalNumOrbits() const;

	unsigned int GetMinPathLength(int origin, int dest, std::vector<int>& visitedNodes) const;
	int GetMinTransfersToSanta();

private:
	std::vector<OrbitObject> m_OrbitList;
};