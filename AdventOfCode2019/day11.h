#pragma once

#include "dailychallenge.h"

#include "intcodecomputer.h"

class Day11 : public DailyChallenge
{
protected:
	virtual const char* GetInputSourceFile() const override { return "input/day11.txt"; }

	virtual void ChallengeA() override;
	virtual void ChallengeB() override;

private:
	struct HullPosition
	{
		int m_X = 0;
		int m_Y = 0;
		bool m_IsWhite = false;

		bool operator<(const HullPosition& other) const;
	};

	using HullPositionList = std::vector<HullPosition>;
	using HullPositionListIt = HullPositionList::iterator;

	void PaintHull(bool isInitialPosWhite);
	void PrintHull();
private:
	std::vector<HullPosition> m_PaintedPositions;
	IntcodeComputer m_Computer;
};