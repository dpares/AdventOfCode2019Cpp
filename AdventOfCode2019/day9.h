#pragma once

#include "dailychallenge.h"

#include "intcodecomputer.h"

class Day9 : public DailyChallenge
{
protected:
	virtual const char* GetInputSourceFile() const override { return "input/day9.txt"; }

	virtual void ChallengeA() override;
	virtual void ChallengeB() override;

private:
	IntcodeComputer m_Computer;
};