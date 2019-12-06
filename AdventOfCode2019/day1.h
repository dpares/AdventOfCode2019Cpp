#pragma once

#include "dailychallenge.h"

class Day1 : public DailyChallenge
{
protected:
	virtual const char* GetInputSourceFile() const override { return "input/day1.txt"; }

	virtual void ChallengeA() override;
	virtual void ChallengeB() override;

private:
	int RequiredFuel(int mass);
};