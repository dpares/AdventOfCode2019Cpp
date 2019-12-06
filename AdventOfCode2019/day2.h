#pragma once

#include "dailychallenge.h"
#include "intcodecomputer.h"

class Day2 : public DailyChallenge
{
protected:
	virtual const char* GetInputSourceFile() const override { return "input/day2.txt"; }

	virtual void ChallengeA() override;
	virtual void ChallengeB() override;

private:
	IntcodeComputer m_Computer;
};